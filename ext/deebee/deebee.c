#include <deebee.h>

VALUE mSqlite3;
VALUE cDeeBee;

static VALUE libversion(VALUE klass)
{
  return INT2NUM(sqlite3_libversion_number());
}

static VALUE open_connection(VALUE klass, VALUE file)
{
  sqlite3 * database;
  if(SQLITE_OK != sqlite3_open(StringValuePtr(file), &database)) {
    rb_raise(rb_eRuntimeError, "%s", sqlite3_errmsg(database));
  }

  return Data_Wrap_Struct(klass, 0, 0, database);
}

static VALUE prepare(VALUE self, VALUE sql)
{
  sqlite3 * ctx;
  sqlite3_stmt *stmt;

  Data_Get_Struct(self, sqlite3, ctx);
  int status = sqlite3_prepare_v2(
      ctx,
      StringValuePtr(sql), // TODO: convert this to UTF-8
      RSTRING_LEN(sql),
      &stmt,
      NULL
  );

  if(SQLITE_OK != status)
    rb_raise(rb_eRuntimeError, "%s", sqlite3_errmsg(ctx));

  VALUE statement = Data_Wrap_Struct(cDeeBeeStatement, 0, 0, stmt);
  rb_iv_set(statement, "@connection", self);

  return statement;
}

int enc_cb(void * _self, int columns, char **data, char **names)
{
  VALUE self = (VALUE)_self;
  int index = rb_enc_find_index("UTF-8");
  VALUE enc = rb_str_new2(data[0]);
  rb_enc_associate_index(enc, index);

  rb_iv_set(self, "@encoding", enc);

  return 0;
}

static VALUE encoding_str(VALUE self)
{
  sqlite3 * ctx;

  Data_Get_Struct(self, sqlite3, ctx);

  sqlite3_exec(ctx, "PRAGMA encoding", enc_cb, (void *)self, NULL);

  return rb_iv_get(self, "@encoding");
}

void Init_deebee()
{
  mSqlite3         = rb_define_module("SQLite3");
  cDeeBee          = rb_define_class_under(mSqlite3, "DeeBee", rb_cObject);

  init_deebee_statement();

  rb_define_singleton_method(cDeeBee, "libversion", libversion, 0);
  rb_define_singleton_method(cDeeBee, "open", open_connection, 1);
  rb_define_method(cDeeBee, "prepare", prepare, 1);
  rb_define_private_method(cDeeBee, "encoding_str", encoding_str, 0);
}
