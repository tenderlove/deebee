#include <deebee.h>

VALUE cDeeBeeStatement;

static VALUE each(VALUE self)
{
  sqlite3_stmt *stmt;

  Data_Get_Struct(self, sqlite3_stmt, stmt);

  VALUE connection = rb_iv_get(self, "@connection");
  VALUE encoding   = rb_funcall(connection, rb_intern("encoding"), 0);
  int idx  = rb_to_encoding_index(encoding);

  int value = sqlite3_step(stmt);
  while(value != SQLITE_DONE) {
    switch(value) {
      case SQLITE_ROW:
        {
          int length = sqlite3_column_count(stmt);
          VALUE list = rb_ary_new2(length);

          int i;
          for(i = 0; i < length; i++) {
            switch(sqlite3_column_type(stmt, i)) {
              case SQLITE_INTEGER:
                rb_ary_push(list, INT2NUM(sqlite3_column_int(stmt, i)));
                break;
              case SQLITE_FLOAT:
                rb_ary_push(list, rb_float_new(sqlite3_column_double(stmt, i)));
                break;
              case SQLITE_TEXT:
                {
                  VALUE str = rb_str_new2(sqlite3_column_text(stmt, i));
                  rb_enc_associate_index(str, idx);
                  rb_ary_push(list, str);
                }
                break;
              case SQLITE_BLOB:
                rb_ary_push(list, rb_str_new2(sqlite3_column_blob(stmt, i)));
                break;
              case SQLITE_NULL:
                rb_ary_push(list, Qnil);
                break;
              default:
                rb_raise(rb_eRuntimeError, "oh no!");
            }
          }
          rb_yield(list);
        }
        break;
      default:
        rb_raise(rb_eRuntimeError, "oh no!");
    }
    value = sqlite3_step(stmt);
  }
  return self;
}

void init_deebee_statement()
{
  cDeeBeeStatement = rb_define_class_under(cDeeBee, "Statement", rb_cObject);

  rb_define_method(cDeeBeeStatement, "each", each, 0);
}
