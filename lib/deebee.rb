require 'deebee/deebee'
require 'deebee/statement'

module SQLite3
  class DeeBee
    VERSION = '1.0.0'

    def encoding
      Encoding.find(encoding_str)
    end
  end
end
