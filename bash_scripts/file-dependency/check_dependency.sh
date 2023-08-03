#!/usr/bin/env bash


check_dependency() {
    missed_dependency=0
    for dependency in "$@"; do
        if ! command -v "$dependency" &>/dev/null; then
            echo "$dependency, cannot be found, please try to install it"
            missed_dependency=$(($missed_dependency + 1))
        fi
    done

    if [[ $missed_dependency -gt 0 ]]; then
        exit 1
    fi
}

USER_AGENT="Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/114.0"
