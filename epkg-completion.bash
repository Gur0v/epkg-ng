#!/bin/bash

_epkg_completions() {
    local cur prev opts
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    
    local commands="install remove update upgrade search show autoremove autoclean clean forceremove listfiles listinstalled provides depends uses verify verifyall sysinfo moo"
    
    local package_commands="install remove search show forceremove listfiles provides depends uses verify"
    local file_commands="provides"
    
    if [[ ${COMP_CWORD} == 1 ]]; then
        COMPREPLY=($(compgen -W "${commands}" -- ${cur}))
        return 0
    fi
    
    local cmd="${COMP_WORDS[1]}"
    
    case "${cmd}" in
        install)
            _epkg_available_packages
            ;;
        remove|forceremove|listfiles|depends|uses|verify|show)
            _epkg_installed_packages
            ;;
        search)
            _epkg_available_packages
            ;;
        provides)
            _epkg_complete_files
            ;;
        *)
            ;;
    esac
}

_epkg_available_packages() {
    if command -v eix >/dev/null 2>&1; then
        local packages=$(eix --only-names -c | grep "^${cur}" | head -50)
        COMPREPLY=($(compgen -W "${packages}" -- ${cur}))
    fi
}

_epkg_installed_packages() {
    if command -v qlist >/dev/null 2>&1; then
        local packages=$(qlist -I | cut -d/ -f2 | cut -d- -f1 | grep "^${cur}" | sort -u | head -50)
        COMPREPLY=($(compgen -W "${packages}" -- ${cur}))
    elif command -v equery >/dev/null 2>&1; then
        local packages=$(equery -q list '*' | cut -d/ -f2 | cut -d- -f1 | grep "^${cur}" | sort -u | head -50)
        COMPREPLY=($(compgen -W "${packages}" -- ${cur}))
    fi
}

_epkg_complete_files() {
    COMPREPLY=($(compgen -f -- ${cur}))
}

complete -F _epkg_completions epkg
