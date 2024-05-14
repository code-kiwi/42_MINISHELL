if [ -z "$1" ]; then
	echo "Enter the program name as the first argument"
	exit
fi

separator="

--------------------------------

"
if [[ $1 == *"/"* ]];
then
	(cd $(dirname "$1") && make) || exit
fi

$1 < go_wilds.txt
echo "$separator"
read -n1
clear

$1 < pipe.txt
echo "$separator"
read -n1
clear

$1 < redirs.txt
echo "$separator"
read -n1
clear

$1 < test_expansion_full.txt
echo "$separator"
read -n1
clear

$1 < test_logical.txt
echo "$separator"
read -n1
clear

$1 < test_path_cmds.txt
echo "$separator"
read -n1
clear

$1 < test_quote.txt
echo "$separator"
read -n1
clear

$1 < test_right_expansion.txt
echo "$separator"
read -n1
clear

$1 < test_simple_cmd.txt
echo "$separator"
read -n1
clear

$1 < test_syntax.txt
echo "$separator"
clear