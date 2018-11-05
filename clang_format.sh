#!/bin/bash

set -e
set -o pipefail
shopt -s globstar
shopt -s nullglob

# error values
ESUCCESS=0
EREPLACE=1
EINTERNAL=2
EINVAL=3

# variables
PATTERN_DEFAULT='{src,include,test}/**/*.{c,h,cpp,hpp}'
declare -a PATTERNS
unset ACTION
unset CLANG_FORMAT_PATH
unset VERBOSE

function print_help()
{
	printf '%s\n' "\
usage: $0 [OPTION]... check|format

	-c, --clang-format <PATH>
		path to clang-format,
		defaults to the result of 'command -v clang-format'

	-p, --pattern <PATTERN>
		pattern to use to get which files to check,
		defaults to '$PATTERN_DEFAULT' if nothing is specified,
		can be specified multiple times

	-v, --verbose
		print list of files as that are checked

	check
		check sources and report replacements

	format
		format sources in place

	EXIT CODE
		$ESUCCESS	[check] no replacements
			[format] completed ok
		$EREPLACE	[check] found replacements
		$EINTERNAL	internal error
		$EINVAL	invalid arguments
		*	when any commands fails because of 'set -e'"
}

# print usage if no options
if [[ $# == 0 ]]
then
	print_help
	exit $EINVAL
fi

# parse options
while (( $# > 0 ))
do
	case "$1" in
	-c|--clang-format)
		CLANG_FORMAT_PATH="$2"
		shift
		;;
	-h|--help)
		print_help
		exit $ESUCCESS
		;;
	-p|--pattern)
		PATTERNS+=("$2")
		shift
		;;
	-v|--verbose)
		VERBOSE=true
		;;
	check|format)
		ACTION="$1"
		;;
	*)
		printf 'invalid option [%s]\n' "$1"
		exit $EINVAL
		;;
	esac

	shift
done

# action is required
[[ ! -v ACTION ]] && print_help && exit $EINVAL

# set which clang-format binary to use
if [[ -v CLANG_FORMAT_PATH ]]
then
	[[ ! -f "$CLANG_FORMAT_PATH" ]] \
		&& printf '%s: file not found\n' "$CLANG_FORMAT_PATH" \
		&& exit $EINVAL
	clang_format="$CLANG_FORMAT_PATH"
else
	clang_format="$(command -v clang-format)"
fi

# add default pattern if none is given
[[ ${#PATTERNS[@]} == 0 ]] && PATTERNS+=("$PATTERN_DEFAULT")

# set targets
declare -a targets
for p in "${PATTERNS[@]}"
do
	eval "targets+=($p)"
done

[[ ${#targets[@]} == 0 ]] \
	&& printf 'patterns did not result in any targets\n' \
	&& exit $EINVAL

# ensure targets contain distinct values
readarray -d '' -t targets < <(printf '%s\0' "${targets[@]}" | sort -u -z)

# print targets in verbose
[[ $VERBOSE ]] && printf '%s\n' "${targets[@]}"

# run format if requested
if [[ $ACTION == 'format' ]]
then
	"$clang_format" -i -style=file "${targets[@]}"
	exit $ESUCCESS
fi

# checking logic otherwise
xml="$("$clang_format" -output-replacements-xml -style=file "${targets[@]}")"

# do not fail when no replacements
set +e
replacements="$(echo "$xml" | grep -cv \
	-e "^<?xml version='1.0'?>\$" \
	-e "^<replacements xml:space='preserve' incomplete_format='false'>\$" \
	-e "^</replacements>\$")"

case $? in
0)
	printf '%i replacement(s)\n' "$replacements"
	printf '%s\n' "$xml"
	exit $EREPLACE
	;;
1)
	exit $ESUCCESS
	;;
*)
	printf 'internal error\n'
	exit $EINTERNAL
	;;
esac
