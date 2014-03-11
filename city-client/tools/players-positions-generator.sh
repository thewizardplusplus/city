#!/bin/bash

readonly LEVEL_WIDTH=$1
readonly LEVEL_HEIGHT=$2
readonly LEVEL_FILE=$3

function GeneratePositions {
	for x in $(seq 1 $((LEVEL_WIDTH - 2)))
	do
		for y in $(seq 1 $((LEVEL_HEIGHT - 2)))
		do
			echo "$x $y"
		done
	done
}

function GetHeldPositions {
	local -r level_file=$1
	cat $level_file | sed "s/^[0-9]\+ \(tree\|mountain\|castle\) \([0-9]\+\) \([0-9]\+\)/\2 \3/"
}

function SaveDataToTemporaryFile {
	temporary_filename=$(tempfile)
	echo $temporary_filename

	cat > $temporary_filename
}

function FilterHeldPositions {
	readonly TEMPORARY_FILENAME=$(GetHeldPositions $LEVEL_FILE | SaveDataToTemporaryFile)
	cat | grep -Fvx -f $TEMPORARY_FILENAME

	rm $TEMPORARY_FILENAME
}

function FormatPositions {
	cat | sed "s/\([0-9]\+\) \([0-9]\+\)/\tplayers_positions.push_back(sf::Vector2i(\1, \2));/"
}

GeneratePositions | FilterHeldPositions | FormatPositions
