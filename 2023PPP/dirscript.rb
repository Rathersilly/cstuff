# each file named setup repaced with init in cwd
#
require 'fileutils'

p Dir.pwd
Dir.each_child('.') do |c|
  p c
  p c.class
end
