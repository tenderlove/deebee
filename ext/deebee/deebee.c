#include <deebee.h>

VALUE mSqlite3;
VALUE cDeeBee;

static VALUE libversion(VALUE self)
{
  return INT2NUM(sqlite3_libversion_number());
}

void Init_deebee()
{
  mSqlite3 = rb_define_module("SQLite3");
  cDeeBee  = rb_define_class_under(mSqlite3, "DeeBee", rb_cObject);
  rb_define_singleton_method(cDeeBee, "libversion", libversion, 0);
}
