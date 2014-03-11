#!/bin/bash

readonly LEVEL_WIDTH=$1
readonly LEVEL_HEIGHT=$2
readonly MAXIMAL_ENTITIES_NUMBER=$3
readonly ENTITIES=(tree mountain castle)

function GetEntityType {
	echo ${ENTITIES[$((RANDOM % ${#ENTITIES[*]}))]}
}

function GetRandomPosition {
	local -r maximal_position=$1
	echo $((RANDOM % maximal_position))
}

function GenerateEntity {
	local -r type=$1
	local -r position_x=$2
	local -r position_y=$3

	echo "$type $position_x $position_y"
}

function GenerateHorizontalWall {
	local -r position_y=$1

	for ((x=0; x<$LEVEL_WIDTH; x++))
	do
		GenerateEntity mountain $x $position_y
	done
}

function GenerateVerticalWall {
	local -r position_x=$1

	for ((y=0; y<$LEVEL_HEIGHT; y++))
	do
		GenerateEntity mountain $position_x $y
	done
}

function GenerateWalls {
	GenerateHorizontalWall 0
	GenerateVerticalWall $((LEVEL_WIDTH - 1))
	GenerateHorizontalWall $((LEVEL_HEIGHT - 1))
	GenerateVerticalWall 0
}

function GenerateLevel {
	GenerateWalls

	for ((i=0; i<$MAXIMAL_ENTITIES_NUMBER; i++))
	do
		GenerateEntity $(GetEntityType) $(GetRandomPosition $LEVEL_WIDTH) $(GetRandomPosition $LEVEL_HEIGHT)
	done
}

function FilterEntityOnSamePosition {
	cat | rev | sort | rev | uniq -f 2
}

function AddLineNumbers {
	cat | nl -s " " -v 0 -w 1
}

GenerateLevel | FilterEntityOnSamePosition | AddLineNumbers > $4
