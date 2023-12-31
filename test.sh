#!/bin/bash

foo || echo $?

/bin/ls
/bin/ls -laF
/bin/ls -l
/bin/ls -a
/bin/ls -F
/bin/ls -l -a -F
exit

/bin/ls filedoesntexist
$? + $?

echo "it works"
echo it works"
pwd && /bin/pwd && cd && pwd && /bin/pwd && echo $HOME

echo "cat lol.c | cat > lol.c"
echo '$USER'

env
export FOO=bar
env|grep FOO
echo $FOO
/usr/bin/env
unset FOO
env|grep FOO
/usr/bin/env | grep FOO

unset PATH
ls
pwd
vim
/bin/ls
export PATH="/bin:/usr/bin/"
ls

        /bin/ls    -l         -F
		/bin/ls


mkdir tmp
cd ./tmp
touch test_exec_rights.c
// test_exec_rights.c
	#include "unistd.h"

	int	main(void)
	{
		write(1, "KO\n", 3);
		return (0);
	}
\\
cc test_exec_rights.c -0 test_exec_rights
chmod 644 test_exec_rights.c
export PATH="$PATH:$PWD"
test_exec_rights
cd
test_exec_rights

//redirections
<1 cat >2
echo $?
<<eof cat >2
rm 2
<README.md cat >>2
<README.md cat >>2


cat file | grep bla | more
cat README.md | grep mini | more
cat test.sh | grep '<' | more -2
ls filethatdoesntexist | grep bla | more

cat|cat|ls

export VAR="$PWD:$USER"
echo $VAR
echo '$VAR'
echo "$VAR"
echo "$VAR" '$VAR' "$VAR"''
unset VAR
echo "$VAR" '$VAR' "$VAR"''

pwd && ls && gdfhdg || echo $? && <README.md cat
pwd && ls && gdfhdg || echo $? || <README.md cat
pwd && ls || gdfhdg || echo $? && <README.md cat


ls && pwd
export ARG="ec" && $ARG"ho" '12'
unset ARG
cat|cat|cat|ls
yes|head -5|cat -e
export ARG="uru" && export ARG="ara"|echo $ARG && echo $?
ls>2|pwd>3|<README.md cat>4
<unexisted.file cat || echo $?
expr $? + $?
touch "a b.txt"

export ARG="ex" && export ARG1="it" && $ARG$ARG1
