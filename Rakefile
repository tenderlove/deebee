# -*- ruby -*-

require 'rubygems'
require 'hoe'
require "rake/extensiontask"

Hoe.plugin :debugging, :doofus, :git

Hoe.spec 'deebee' do
  developer 'Aaron Patterson', 'aaronp@rubyforge.org'
  self.readme_file   = 'README.rdoc'
  self.history_file  = 'CHANGELOG.rdoc'
  self.extra_rdoc_files  = FileList['*.rdoc']

  Rake::ExtensionTask.new "deebee", spec do |ext|
    ext.lib_dir = File.join(*['lib', 'deebee', ENV['FAT_DIR']].compact)
  end
end

# vim: syntax=ruby
