
#####	Variables	####





####	Commands	####
#!bin/bash

function test()
{
	T_MINI=$(echo $@ "; exit" |  ./minishell 2>&-)
	T_BASH=$(echo $@ "; exit"| bash 2>&-)
	if [[ "$T_MINI" == "$T_BASH" ]]; then
		printf " %s" "✓ "
	else
		#echo ${T_MINI}
		echo ${T_BASH}
		printf " %s" "✗ "
	fi
	echo
	sleep 0.1
}
echo

#echo
echo 'Teste echo'
echo
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
#echo "Teste exit"
#test 'exit 3'
#test 'exit 3412'
#test 'exit -4'
#test 'fdd'

#PWD
#echo "Teste pwd"
#test 'pwd'
#test 'pwd oi & 6 %'
#test 'unset PWD'
#test 'pwd'
#test 'export PWD=to_na_42'
#test 'pwd'
#test 'mkdir tmp'
#test 'cd ./temp'
#test 'chmod -x ../temp'
#test 'pwd'

#CD
#echo 'Teste echo'
#test 'cd /home'
#test 'pwd'
#test 'cd ..'
#test 'pwd'
#test 'cd /home vai_aonde?'
#test 'echo $?' #não o motivo desse teste perguntar para o Gustavo

