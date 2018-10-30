.PHONY: help build test

DEFAULT_GOAL := build
OBJ = "kcc"

SRC_FILE_LIST = main.c lex.c parser.c ast.c

build: ## build target binary
	gcc $(SRC_FILE_LIST) -I . -o $(OBJ)

help: ## help command
	@echo "help"

test: ## build test bintest and run.
	@echo "TBD"
