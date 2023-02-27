
#####	Variables	####





####	Commands	####
#!bin/bash

function test()
{
	T_MINI=$(echo $@  | ./minishell 2>&-)
	T_BASH=$(echo $@ "; exit" | bash 2>&-)
	if [[ "$T_MINI" == "$T_BASH" ]]; then
		printf " %s" "✓ "
	else
		echo "T1 "${#TEST1}
		echo "T2 "${#TEST2}
		printf " %s" "✗ "
	fi
	echo
	sleep 0.1
}
echo

#echo
echo "Teste echo"
test 'echo'
test 'echo echo'
test 'echo hello'
test 'echo hello morgen'
test 'echo -n morgen'
test 'echo -nn morgen'
test 'echo -n -n -n morgen'
test 'echo -n -nnnnn -n morgen'
test 'echo-n -n -nnf morgen'

#Exit
echo "Teste exit"
test 'exit 3'
test 'exit 3412'
test 'exit -4'
test 'fdd'

