# This file is overwritten during software install.
# Persistent customizations should go in a .local file.
include /etc/firejail/google-chrome-beta.local

# Google Chrome beta browser profile
noblacklist ~/.config/google-chrome-beta
noblacklist ~/.cache/google-chrome-beta
noblacklist ~/.pki
include /etc/firejail/disable-common.inc
include /etc/firejail/disable-programs.inc

# chromium is distributed with a perl script on Arch
# include /etc/firejail/disable-devel.inc
#

netfilter

whitelist ${DOWNLOADS}
mkdir ~/.config/google-chrome-beta
whitelist ~/.config/google-chrome-beta
mkdir ~/.cache/google-chrome-beta
whitelist ~/.cache/google-chrome-beta
mkdir ~/.pki
whitelist ~/.pki
include /etc/firejail/whitelist-common.inc

# lastpass, keepass
# for keepass we additionally need to whitelist our .kdbx password database
whitelist ~/.keepass
whitelist ~/.config/keepass
whitelist ~/.config/KeePass
whitelist ~/.lastpass
whitelist ~/.config/lastpass
