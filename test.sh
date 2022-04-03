#! /bin/bash

RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
MAGENTA="\e[35m"
ENDCOLOR="\e[0m"

# echo -e "${GREEN}APPROVED ${YELLOW}WARNING ${BLUE}OK ${MAGENTA}FAIL ${ENDCOLOR}"
echo -e "${GREEN}PIPEX TESTER${ENDCOLOR}"

test () {
	INFILE=$2
	CMD1=$3
	CMD2=$4

	printf "${BLUE}$1${ENDCOLOR}\n"
	< ${INFILE} ${CMD1} | ${CMD2} > outfile_std
	EXITCODE=$?
	./pipex ${INFILE} "${CMD1}" "${CMD2}" outfile
	EXITCODE_STD=$?
	if cmp -s outfile outfile_std; then
		printf "${GREEN}\tout: OK${ENDCOLOR}"
	else
		printf "${MAGENTA}\tout: KO${ENDCOLOR}"
		diff outfile_std outfile
	fi
	if [ ${EXITCODE} -eq ${EXITCODE_STD} ]; then
		printf "${GREEN}\t\texit code: OK${ENDCOLOR}"
	else
		printf "${MAGENTA}\t\texit code: KO${ENDCOLOR}"
	fi
	echo
}

test 'test: < infile ls -l | wc -l > outfile' \
	'infile' 'ls -l' 'wc -l'
test 'test: < PIPEXaminator/files_in/file_in cat -e | grep gewoon > outfile' \
	'PIPEXaminator/files_in/file_in' 'cat -e' 'grep gewoon'

# test
# PIPEXaminator/files_in/file_in "cat -t" "grep FANTASTISCH" files_out/res_mine
# test
# PIPEXaminator/files_in/file_in "ls -a" "grep pipex" files_out/res_mine
# test
# PIPEXaminator/files_in/file_in "ls -l" "wc -l" files_out/res_mine
# test
# PIPEXaminator/files_in/file_in "ls -l" "wc" files_out/res_mine
# test
# PIPEXaminator/fiwefcen/fileewe_in "cat -e" "grep gewoon" files_out/res_mine
# test
# PIPEXaminator/files_in/file_in "whateverrr" "ls" files_out/res_mine
# test
# PIPEXaminator/files_in/file_in "whateverrr" "nothing" files_out/res_mine
# test
# PIPEXaminator/files_in/file_in "ls" "nopeee" files_out/res_mine
# test
# PIPEXaminator/files_in/file_in "" ""
# test
# PIPEXaminator/files_in/file_in "cat" ""
# test
# PIPEXaminator/files_in/file_in "cat" "grep gewoon"
# test
# PIPEXaminator/files_in/file_in "cat -bestaatniet" "grep FANTASTISCH" files_out/res_mine
# test
# PIPEXaminator/files_in/file_in "cat -t" "cat -bestaatniet FANTASTISCH" files_out/res_mine
# test
# PIPEXaminator/files_in/file_in "cat -t" "grep -bestaatniet FANTASTISCH" files_out/res_mine
