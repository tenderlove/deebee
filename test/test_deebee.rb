require "test/unit"
require "deebee"

class TestDeebee < Test::Unit::TestCase
  def test_libversione
    assert_not_nil SQLite3::DeeBee.libversion
  end
end
