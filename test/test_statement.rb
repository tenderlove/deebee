# -*- coding: utf-8 -*-

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

  def test_string_encoding
    db     = SQLite3::DeeBee.open(File.join(Dir.tmpdir, 'foo.db'))
    string = nil
    test   = "日本語は楽しい"

    stmt   = db.prepare("select '#{test}'")
    stmt.each { |row| string = row.first }

    utf8 = Encoding.find('UTF-8')
    assert_equal utf8, string.encoding
    assert_equal test, string
    assert_equal db.encoding, string.encoding
  end

  def test_string_encoding_euc_jp
    db     = SQLite3::DeeBee.open(File.join(Dir.tmpdir, 'foo.db'))
    string = nil
    test   = "日本語は楽しい"

    sql = "select '#{test}'".encode('EUC-JP')
    stmt   = db.prepare sql
    assert_equal "EUC-JP", sql.encoding.name

    stmt.each { |row| string = row.first }

    utf8 = Encoding.find('UTF-8')
    assert_equal utf8, string.encoding
    assert_equal test, string
    assert_equal db.encoding, string.encoding
  end
end
