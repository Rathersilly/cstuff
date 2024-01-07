# messing around reimplementing colorize with method_missing for no reason
Codes = { reset: '0', bold: '1', faint: '2', italic: '3',
          underline: '4', slow_blink: '5', rapid_blink: '6',
          invert: '7', conceal: '8', strikethrough: '9', green: '32',
          yellow: '33', blue: '34', magenta: '35', cyan: '36', white: '37',
          bright_black: '90', bright_red: '91', bright_green: '92',
          bright_yellow: '93', bright_blue: '94', bright_magenta: '95',
          bright_cyan: '96', bright_white: '97' }
#
#
# create escape string
def es(*args)
  "\e[#{args.map { |x| Codes[x] }.join(';')}m"
end

class String
  def green
    es(:green) + self + es(:reset)
  end

  def yellow
    # Codes[:yellow] + self
    es(:yellow)
    es(:reset)
  end

  def method_missing(*args)
    memo = self
    args.each do |m|
      next unless Codes.keys.include?(m)

      print 'defining: '
      p m
      String.define_method(m) do
        es(m) + self + es(:reset)
      end
      memo = memo.send(m)
    end
    memo
  end

  def bold
    es(:bold) + self + es(:reset)
    # Codes[:bold] + self
  end
end
puts es(:bold, :green) + 'hello'
# explicitely defined
puts 'yellow'.yellow
puts 'green'.green

# defined with method_missing
puts 'str.blue.bold defined with method_missing'.blue.bold
puts 'blue'.blue
puts 'blue'.blue.hello.bold.rapid_blink
puts 'blue'.green.bold.strikethrough.slow_blink
puts 'blue'.green.slow_blink

str = 'QWER'
puts str.blue.size
puts str.size
