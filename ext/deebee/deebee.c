#include <deebee.h>

VALUE mSqlite3;
VALUE cDeeBee;
VALUE cDeeBeeStatement;

static VALUE libversion(VALUE klass)
{
  return INT2NUM(sqlite3_libversion_number());
}

static VALUE open_connection(VALUE klass, VALUE file)
{
  sqlite3 * database;
  if(SQLITE_OK != sqlite3_open(StringValuePtr(file), &database)) {
    rb_raise(rb_eRuntimeError, "fixme!");
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

  return Data_Wrap_Struct(cDeeBeeStatement, 0, 0, stmt);
}

void Init_deebee()
{
  mSqlite3         = rb_define_module("SQLite3");
  cDeeBee          = rb_define_class_under(mSqlite3, "DeeBee", rb_cObject);
  cDeeBeeStatement = rb_define_class_under(cDeeBee, "Statement", rb_cObject);

  rb_define_singleton_method(cDeeBee, "libversion", libversion, 0);
  rb_define_singleton_method(cDeeBee, "open", open_connection, 1);
  rb_define_method(cDeeBee, "prepare", prepare, 1);
}
