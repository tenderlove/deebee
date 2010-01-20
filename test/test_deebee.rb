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

  def test_encoding
    enc = Encoding.find('UTF-8')
    db = SQLite3::DeeBee.open(File.join(Dir.tmpdir, 'foo.db'))
    assert_equal enc, db.encoding
  end
end
