#! /bin/bash

RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
MAGENTA="\e[35m"
ENDCOLOR="\e[0m"
REPORT=""

# echo -e "${GREEN}APPROVED ${YELLOW}WARNING ${BLUE}OK ${MAGENTA}FAIL ${ENDCOLOR}"
echo -e "${GREEN}PIPEX TESTER${ENDCOLOR}"

report () {
	TEST=$1
	MSG=$2
	RECEIVED=$3
	EXPECTED=$4

	REPORT+="\n${TEST}\
			\n\t${YELLOW}${MSG}${ENDCOLOR}\
			\n\t${BLUE}Expected: ${EXPECTED}${ENDCOLOR}\
			\n\t${MAGENTA}Received: ${RECEIVED}${ENDCOLOR}\n"
}

test () {
	INFILE=$2
	CMD1=$3
	CMD2=$4

	printf "${BLUE}$1${ENDCOLOR}\n"
	ERRORMSG=$( < ${INFILE} ${CMD1} | ${CMD2} > outfile_std 2>&1 )
	EXITCODE=$?
	sleep 0.1
	ERRORMSG_STD=$( ./pipex ${INFILE} "${CMD1}" "${CMD2}" outfile 2>&1 )
	EXITCODE_STD=$?
	sleep 0.1
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
		report "$1" "Wrong exit code:" ${EXITCODE_STD} ${EXITCODE}
	fi
	if [ "${ERRORMSG}" = "${ERRORMSG_STD}" ]; then
		printf "${GREEN}\t\terror message: OK${ENDCOLOR}"
	else
		printf "${MAGENTA}\t\terror message: KO${ENDCOLOR}"
		report "$1" "Wrong error message:" "${ERRORMSG_STD}" "${ERRORMSG}"
	fi
	# rm outfile outfile_std
	echo
}

test 'test A: < infile ls -l | wc -l > outfile' \
	'infile' 'ls -l' 'wc -l'
test 'test B: < infile grep a1 | wc -w > outfile' \
	'infile' 'grep a1' 'wc -w'
test 'test 01: < not_file ls -l | wc -l > outfile' \
	'infile' 'ls -l' 'wc -l'
# test 'test 02: < PIPEXaminator/files_in/file_in cat -e | grep gewoon > outfile' \
# 	'PIPEXaminator/files_in/file_in' 'cat -e' 'grep gewoon'
# test 'test 03: < PIPEXaminator/files_in/file_in cat -t | grep FANTASTISCH > files_out/res_mine' \
# 	'PIPEXaminator/files_in/file_in' "cat -t" "grep FANTASTISCH" 'files_out/res_mine'
# test 'test 04: < PIPEXaminator/files_in/file_in ls -a | grep pipex > files_out/res_mine' \
# 	'PIPEXaminator/files_in/file_in' "ls -a" "grep pipex" 'files_out/res_mine'
# test 'test 05: < PIPEXaminator/files_in/file_in ls -l | wc -l > files_out/res_mine' \
# 	'PIPEXaminator/files_in/file_in' "ls -l" "wc -l" 'files_out/res_mine'
# test 'test 06: < PIPEXaminator/files_in/file_in ls -l | wc > files_out/res_mine' \
# 	'PIPEXaminator/files_in/file_in' "ls -l" "wc" 'files_out/res_mine'
test 'test 07: < PIPEXaminator/fiwefcen/fileewe_in cat -e | grep gewoon > files_out/res_mine' \
	'PIPEXaminator/fiwefcen/fileewe_in' "cat -e" "grep gewoon" 'files_out/res_mine'
test 'test 08: < whatever | ls > files_out/res_mine' \
	'PIPEXaminator/files_in/file_in' "whatever" "ls" 'files_out/res_mine'
test 'test 09: < whatever | nothing > files_out/res_mine' \
	'PIPEXaminator/files_in/file_in' "whatever" "nothing" 'files_out/res_mine'
# test 'test 10: < ls | nothing > files_out/res_mine' \
# 	'PIPEXaminator/files_in/file_in' "ls" "nothing" 'files_out/res_mine'
# test 'test 11: < PIPEXaminator/files_in/file_in' \
# 	'PIPEXaminator/files_in/file_in' "" ""
# test 'test 12: < PIPEXaminator/files_in/file_in cat' \
# 	'PIPEXaminator/files_in/file_in' "cat" ""
# test 'test 13: < PIPEXaminator/files_in/file_in cat | grep gewoon' \
# 	'PIPEXaminator/files_in/file_in' "cat" "grep gewoon"
# test 'test 14: < cat -bestaatniet | grep FANTASTISCH > files_out/res_mine' \
# 	'PIPEXaminator/files_in/file_in' "cat -bestaatniet" "grep FANTASTISCH" 'files_out/res_mine'
# test 'test 15: < cat -t | cat -bestaatniet FANTASTISCH > files_out/res_mine' \
# 	'PIPEXaminator/files_in/file_in' "cat -t" "cat -bestaatniet FANTASTISCH" 'files_out/res_mine'
# test 'test 16: < cat -t | grep -bestaatniet FANTASTISCH > files_out/res_mine' \
# 	'PIPEXaminator/files_in/file_in' "cat -t" "grep -bestaatniet FANTASTISCH" 'files_out/res_mine'

echo -e ${REPORT}
