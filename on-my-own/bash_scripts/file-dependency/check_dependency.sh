#!/usr/bin/env bash


check_dependency() {
    missed_dependency=0
    for dependency in $@; do
        if ! command -v "$dependency" &>/dev/null; then
            echo "$dependency, cannot be found, please try to install it"
            missed_dependency=$(($missed_dependency + 1))
        fi
    done

    return $missed_dependency
}
