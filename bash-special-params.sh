# $1, $2, $3, ... (Positional Parameters):
echo "First argument: $1, Second argument: $2, Third argument: $3"
# "$@" (Array-like construct of all positional parameters):
for arg in "$@"; do echo "$arg"; done
# "$*" (IFS expansion of all positional parameters):
echo "$*"
# $# (Number of positional parameters):
echo "Number of arguments: $#"
# $- (Current options set for the shell):
echo "Current options: $-"
# $$ (PID of the current shell):
echo "PID of the current shell: $$"
# $_ (Most recent parameter or abs path of the command to start the shell):
echo "Most recent parameter: $_"
# $IFS (Input field separator):
echo "IFS value: $IFS"
# $? (Most recent foreground pipeline exit status):
echo "Exit status of the last command: $?"
# $! (PID of the most recent background command):
echo "PID of the most recent background command: $!"
# $0 (Name of the shell or shell script):
echo "Name of the script: $0"

