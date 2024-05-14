if [ -z "$1" ]; then
	echo "Enter the program name as the first argument"
	exit
fi

GREEN='\033[0;32m'
RESET_COLOR='\033[0m'

separator="

--------------------------------

"
if [[ $1 == *"/"* ]];
then
	(cd $(dirname "$1") && make) || exit
fi

echo -e $GREEN
echo        " #######################################
 #                                     #
 #              go_wilds               #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < go_wilds.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #           go_wilds_bonus            #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < go_wilds_bonus.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #                pipe                 #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < pipe.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #                redirs               #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < redirs.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #        test_expansion_full          #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < test_expansion_full.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #            test_logical             #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < test_logical.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #          test_path_cmds             #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < test_path_cmds.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #             test_quote              #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < test_quote.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #        test_right_expansion         #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < test_right_expansion_type.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #          test_simple_cmds           #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < test_simple_cmd.txt
echo "$separator"
tput cup 0 0
read -n1
clear

echo -e $GREEN
echo        " #######################################
 #                                     #
 #           test_syntax               #
 #                                     #
 #######################################"
echo -e $RESET_COLOR
$1 < test_syntax.txt
echo "copy this into the shell : "
cat test_syntax.txt
$1
echo "$separator"
tput cup 0 0
read -n1
clear

rm tmp_out*
rm tmp_redir*