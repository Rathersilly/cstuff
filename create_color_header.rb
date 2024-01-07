AnsiCodes = { reset: '0', bold: '1', faint: '2', italic: '3',
              underline: '4', slow_blink: '5', rapid_blink: '6',
              invert: '7', conceal: '8', strikethrough: '9', green: '32',
              yellow: '33', blue: '34', magenta: '35', cyan: '36', white: '37',
              bright_black: '90', bright_red: '91', bright_green: '92',
              bright_yellow: '93', bright_blue: '94', bright_magenta: '95',
              bright_cyan: '96', bright_white: '97' }
output = ''
# define INFO std::cout << "\t" << __PRETTY_FUNCTION__ << std::endl;
# define RESET "\033[0m"
# define BOLD "\033[1m"    /* Red */

# methods of adding color - macros and namespace functions and structs

# Macros

ESC = "\e["
CMD = 'm'

result = ''
AnsiCodes.each do |k, v|
  result << "#define #{k.upcase} \"#{ESC}#{v}#{CMD}\"\n"
end
p result
File.open('color_macros.h', 'w') do |f|
  f.write(result)
end
result = ''
