require "test/unit"
require "deebee"
require 'tmpdir'

class TestDeebee < Test::Unit::TestCase
  def test_libversione
    assert_not_nil SQLite3::DeeBee.libversion
  end

  def test_open
    db = SQLite3::DeeBee.open(File.join(Dir.tmpdir, 'foo.db'))
  end

  def test_prepare
    db = SQLite3::DeeBee.open(File.join(Dir.tmpdir, 'foo.db'))
    stmt = db.prepare('PRAGMA encoding')
    assert_instance_of(SQLite3::DeeBee::Statement, stmt);
  end
end
