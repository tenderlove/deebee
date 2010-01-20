require "test/unit"
require "deebee"
require 'tmpdir'

class TestStatement < Test::Unit::TestCase
  def test_step
    db = SQLite3::DeeBee.open(File.join(Dir.tmpdir, 'foo.db'))
    stmt = db.prepare('PRAGMA encoding')
    called = false
    stmt.each { |row| called = true }
    assert called
  end
end
