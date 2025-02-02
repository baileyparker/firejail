/*
 * Copyright (C) 2014-2017 Firejail Authors
 *
 * This file is part of firejail project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef FIREJAIL_H
#define FIREJAIL_H
#include "../include/common.h"
#include "../include/euid_common.h"

// debug restricted shell
//#define DEBUG_RESTRICTED_SHELL

// filesystem
#define RUN_FIREJAIL_BASEDIR	"/run"
#define RUN_FIREJAIL_DIR	"/run/firejail"
#define RUN_FIREJAIL_APPIMAGE_DIR	"/run/firejail/appimage"
#define RUN_FIREJAIL_NAME_DIR	"/run/firejail/name"
#define RUN_FIREJAIL_X11_DIR	"/run/firejail/x11"
#define RUN_FIREJAIL_NETWORK_DIR	"/run/firejail/network"
#define RUN_FIREJAIL_BANDWIDTH_DIR	"/run/firejail/bandwidth"
#define RUN_NETWORK_LOCK_FILE	"/run/firejail/firejail.lock"
#define RUN_RO_DIR	"/run/firejail/firejail.ro.dir"
#define RUN_RO_FILE	"/run/firejail/firejail.ro.file"
#define RUN_MNT_DIR	"/run/firejail/mnt"	// a tmpfs is mounted on this directory before any of the files below are created
#define RUN_CGROUP_CFG	"/run/firejail/mnt/cgroup"
#define RUN_CPU_CFG	"/run/firejail/mnt/cpu"
#define RUN_GROUPS_CFG	"/run/firejail/mnt/groups"
#define RUN_PROTOCOL_CFG	"/run/firejail/mnt/protocol"
#define RUN_HOME_DIR	"/run/firejail/mnt/home"
#define RUN_ETC_DIR	"/run/firejail/mnt/etc"
#define RUN_OPT_DIR	"/run/firejail/mnt/opt"
#define RUN_SRV_DIR	"/run/firejail/mnt/srv"
#define RUN_BIN_DIR	"/run/firejail/mnt/bin"
#define RUN_PULSE_DIR	"/run/firejail/mnt/pulse"

#define RUN_SECCOMP_PROTOCOL	"/run/firejail/mnt/seccomp.protocol"	// protocol filter
#define RUN_SECCOMP_CFG	"/run/firejail/mnt/seccomp"			// configured filter
#define RUN_SECCOMP_AMD64	"/run/firejail/mnt/seccomp.amd64"	// amd64 filter installed on i386 architectures
#define RUN_SECCOMP_I386	"/run/firejail/mnt/seccomp.i386"		// i386 filter installed on amd64 architectures
#define PATH_SECCOMP_DEFAULT (LIBDIR "/firejail/seccomp")			// default filter built during make
#define PATH_SECCOMP_DEFAULT_DEBUG (LIBDIR "/firejail/seccomp.debug")	// default filter built during make
#define PATH_SECCOMP_AMD64 (LIBDIR "/firejail/seccomp.amd64")		// amd64 filter built during make
#define PATH_SECCOMP_I386 (LIBDIR "/firejail/seccomp.i386")			// i386 filter built during make


#define RUN_DEV_DIR		"/run/firejail/mnt/dev"
#define RUN_DEVLOG_FILE	"/run/firejail/mnt/devlog"

#define RUN_WHITELIST_X11_DIR	"/run/firejail/mnt/orig-x11"
#define RUN_WHITELIST_HOME_DIR	"/run/firejail/mnt/orig-home"	// default home directory masking
#define RUN_WHITELIST_HOME_USER_DIR	"/run/firejail/mnt/orig-home-user"	// home directory whitelisting
#define RUN_WHITELIST_TMP_DIR	"/run/firejail/mnt/orig-tmp"
#define RUN_WHITELIST_MEDIA_DIR	"/run/firejail/mnt/orig-media"
#define RUN_WHITELIST_MNT_DIR	"/run/firejail/mnt/orig-mnt"
#define RUN_WHITELIST_VAR_DIR	"/run/firejail/mnt/orig-var"
#define RUN_WHITELIST_DEV_DIR	"/run/firejail/mnt/orig-dev"
#define RUN_WHITELIST_OPT_DIR	"/run/firejail/mnt/orig-opt"
#define RUN_WHITELIST_SRV_DIR   "/run/firejail/mnt/orig-srv"

#define RUN_XAUTHORITY_FILE	"/run/firejail/mnt/.Xauthority"
#define RUN_XAUTHORITY_SEC_FILE	"/run/firejail/mnt/sec.Xauthority"
#define RUN_ASOUNDRC_FILE	"/run/firejail/mnt/.asoundrc"
#define RUN_HOSTNAME_FILE	"/run/firejail/mnt/hostname"
#define RUN_HOSTS_FILE	"/run/firejail/mnt/hosts"
#define RUN_RESOLVCONF_FILE	"/run/firejail/mnt/resolv.conf"
#define RUN_MACHINEID	"/run/firejail/mnt/machine-id"
#define RUN_LDPRELOAD_FILE	"/run/firejail/mnt/ld.so.preload"
#define RUN_UTMP_FILE		"/run/firejail/mnt/utmp"
#define RUN_PASSWD_FILE		"/run/firejail/mnt/passwd"
#define RUN_GROUP_FILE		"/run/firejail/mnt/group"
#define RUN_FSLOGGER_FILE		"/run/firejail/mnt/fslogger"



// profiles
#define DEFAULT_USER_PROFILE	"default"
#define DEFAULT_ROOT_PROFILE	"server"
#define MAX_INCLUDE_LEVEL 6		// include levels in profile files


#define ASSERT_PERMS(file, uid, gid, mode) \
	do { \
		assert(file);\
		struct stat s;\
		if (stat(file, &s) == -1) errExit("stat");\
		assert(s.st_uid == uid);\
		assert(s.st_gid == gid);\
		assert((s.st_mode & 07777) == (mode));\
	} while (0)
#define ASSERT_PERMS_FD(fd, uid, gid, mode) \
	do { \
		struct stat s;\
		if (fstat(fd, &s) == -1) errExit("fstat");\
		assert(s.st_uid == uid);\
		assert(s.st_gid == gid);\
		assert((s.st_mode & 07777) == (mode));\
	} while (0)
#define ASSERT_PERMS_STREAM(file, uid, gid, mode) \
	do { \
		int fd = fileno(file);\
		if (fd == -1) errExit("fileno");\
		ASSERT_PERMS_FD(fd, uid, gid, (mode));\
	} while (0)

#define SET_PERMS_FD(fd, uid, gid, mode) \
	do { \
		if (fchmod(fd, (mode)) == -1)	errExit("chmod");\
		if (fchown(fd, uid, gid) == -1) errExit("chown");\
	} while (0)
#define SET_PERMS_STREAM(stream, uid, gid, mode) \
	do { \
		int fd = fileno(stream);\
		if (fd == -1) errExit("fileno");\
		SET_PERMS_FD(fd, uid, gid, (mode));\
	} while (0)
#define SET_PERMS_STREAM_NOERR(stream, uid, gid, mode) \
	do { \
		int fd = fileno(stream);\
		if (fd == -1) continue;\
		int rv = fchmod(fd, (mode));\
		(void) rv;\
		rv = fchown(fd, uid, gid);\
		(void) rv;\
	} while (0)

// main.c
typedef struct bridge_t {
	// on the host
	char *dev;		// interface device name: bridge or regular ethernet
	uint32_t ip;		// interface device IP address
	uint32_t mask;		// interface device mask
	uint8_t mac[6];		// interface mac address
	int mtu;		// interface mtu
	
	char *veth_name;	// veth name for the device connected to the bridge
	
	// inside the sandbox
	char *devsandbox;	// name of the device inside the sandbox
	uint32_t ipsandbox;	// ip address inside the sandbox
	char *ip6sandbox;	// ipv6 address inside the sandbox
	uint8_t macsandbox[6]; // mac address inside the sandbox
	uint32_t iprange_start;// iprange arp scan start range
	uint32_t iprange_end;	// iprange arp scan end range
	
	// flags
	uint8_t arg_ip_none;	// --ip=none
	uint8_t macvlan;	// set by --net=eth0 (or eth1, ...); reset by --net=br0 (or br1, ...)
	uint8_t configured;
	uint8_t scan;		// set by --scan
}  Bridge;

typedef struct interface_t {
	char *dev;
	uint32_t ip;
	uint32_t mask;
	uint8_t mac[6];
	int mtu;
	
	uint8_t configured;
} Interface;

typedef struct profile_entry_t {
	struct profile_entry_t *next;
	char *data;	// command
	
	// whitelist command parameters
	char *link;	// link name - set if the file is a link
	unsigned home_dir:1;	// whitelist in /home/user directory
	unsigned tmp_dir:1;	// whitelist in /tmp directory
	unsigned media_dir:1;	// whitelist in /media directory
	unsigned mnt_dir:1;	// whitelist in /mnt directory
	unsigned var_dir:1;	// whitelist in /var directory
	unsigned dev_dir:1;	// whitelist in /dev directory
	unsigned opt_dir:1;	// whitelist in /opt directory
        unsigned srv_dir:1;     // whitelist in /srv directory
}ProfileEntry;

typedef struct config_t {
	// user data
	char *username;
	char *homedir;
	
	// filesystem
	ProfileEntry *profile;
#define MAX_PROFILE_IGNORE 32	
	char *profile_ignore[MAX_PROFILE_IGNORE];
	char *chrootdir;	// chroot directory
	char *home_private;	// private home directory
	char *home_private_keep;	// keep list for private home directory
	char *etc_private_keep;	// keep list for private etc directory
	char *opt_private_keep;	// keep list for private opt directory
	char *srv_private_keep;	// keep list for private srv directory
	char *bin_private_keep;	// keep list for private bin directory
	char *cwd;		// current working directory
	char *overlay_dir;
	char *private_template; // template dir for tmpfs home

	// networking
	char *name;		// sandbox name
	char *hostname;	// host name
	char *hosts_file;		// hosts file to be installed in the sandbox
	uint32_t defaultgw;	// default gateway
	Bridge bridge0;
	Bridge bridge1;
	Bridge bridge2;
	Bridge bridge3;
	Interface interface0;
	Interface interface1;
	Interface interface2;
	Interface interface3;
	uint32_t dns1;	// up to 3 IP addresses for dns servers
	uint32_t dns2;
	uint32_t dns3;

	// seccomp
	char *seccomp_list;//  optional seccomp list on top of default filter
	char *seccomp_list_drop;	// seccomp drop list
	char *seccomp_list_keep;	// seccomp keep list
	char *protocol;			// protocol list

	// rlimits
	unsigned rlimit_nofile;
	unsigned rlimit_nproc;
	unsigned rlimit_fsize;
	unsigned rlimit_sigpending;
	
	// cpu affinity, nice and control groups
	uint32_t cpus;
	int nice;
	char *cgroup;
	

	// command line
	char *command_line;
	char *window_title;
	char *command_name;
	char *shell;
	char **original_argv;
	int original_argc;
	int original_program_index;
} Config;
extern Config cfg;

static inline Bridge *last_bridge_configured(void) {
	if (cfg.bridge3.configured)
		return &cfg.bridge3;
	else if (cfg.bridge2.configured)
		return &cfg.bridge2;
	else if (cfg.bridge1.configured)
		return &cfg.bridge1;
	else if (cfg.bridge0.configured)
		return &cfg.bridge0;
	else
		return NULL;
}

static inline int any_bridge_configured(void) {
	if (cfg.bridge0.configured || cfg.bridge1.configured || cfg.bridge2.configured || cfg.bridge3.configured)
		return 1;
	else
		return 0;
}

static inline int any_interface_configured(void) {
	if (cfg.interface0.configured || cfg.interface1.configured || cfg.interface2.configured || cfg.interface3.configured)
		return 1;
	else
		return 0;
}
void clear_run_files(pid_t pid);

extern int arg_private;		// mount private /home
extern int arg_private_template; // private /home template
extern int arg_allow_private_blacklist;  // blacklist things in private directories
extern int arg_debug;		// print debug messages
extern int arg_debug_check_filename;		// print debug messages for filename checking
extern int arg_debug_blacklists;	// print debug messages for blacklists
extern int arg_debug_whitelists;	// print debug messages for whitelists
extern int arg_nonetwork;	// --net=none
extern int arg_command;	// -c
extern int arg_overlay;		// overlay option
extern int arg_overlay_keep;	// place overlay diff in a known directory
extern int arg_overlay_reuse;	// allow the reuse of overlays

extern int arg_seccomp;	// enable default seccomp filter

extern int arg_caps_default_filter;	// enable default capabilities filter
extern int arg_caps_drop;		// drop list
extern int arg_caps_drop_all;		// drop all capabilities
extern int arg_caps_keep;		// keep list
extern char *arg_caps_list;		// optional caps list

extern int arg_trace;		// syscall tracing support
extern int arg_tracelog;	// blacklist tracing support
extern int arg_rlimit_nofile;	// rlimit nofile
extern int arg_rlimit_nproc;	// rlimit nproc
extern int arg_rlimit_fsize;	// rlimit fsize
extern int arg_rlimit_sigpending;// rlimit sigpending
extern int arg_nogroups;	// disable supplementary groups
extern int arg_nonewprivs;	// set the NO_NEW_PRIVS prctl
extern int arg_noroot;		// create a new user namespace and disable root user
extern int arg_netfilter;	// enable netfilter
extern int arg_netfilter6;	// enable netfilter6
extern char *arg_netfilter_file;	// netfilter file
extern char *arg_netfilter6_file;	// netfilter file
extern char *arg_netns;		// "ip netns"-created network namespace to use
extern int arg_doubledash;	// double dash
extern int arg_shell_none;	// run the program directly without a shell
extern int arg_private_dev;	// private dev directory
extern int arg_private_etc;	// private etc directory
extern int arg_private_opt;	// private opt directory
extern int arg_private_srv;	// private srv directory
extern int arg_private_bin;	// private bin directory
extern int arg_private_tmp;	// private tmp directory
extern int arg_scan;		// arp-scan all interfaces
extern int arg_whitelist;	// whitelist commad
extern int arg_nosound;	// disable sound
extern int arg_no3d;		// disable 3d hardware acceleration
extern int arg_quiet;		// no output for scripting
extern int arg_join_network;	// join only the network namespace
extern int arg_join_filesystem;	// join only the mount namespace
extern int arg_nice;		// nice value configured
extern int arg_ipc;		// enable ipc namespace
extern int arg_writable_etc;	// writable etc
extern int arg_writable_var;	// writable var
extern int arg_writable_var_log; // writable /var/log
extern int arg_appimage;	// appimage
extern int arg_audit;		// audit
extern char *arg_audit_prog;	// audit
extern int arg_apparmor;	// apparmor
extern int arg_allow_debuggers;	// allow debuggers
extern int arg_x11_block;	// block X11
extern int arg_x11_xorg;	// use X11 security extention
extern int arg_allusers;	// all user home directories visible
extern int arg_machineid;	// preserve /etc/machine-id

extern int login_shell;
extern int parent_to_child_fds[2];
extern int child_to_parent_fds[2];
extern pid_t sandbox_pid;

#define MAX_ARGS 128		// maximum number of command arguments (argc)
extern char *fullargv[MAX_ARGS];
extern int fullargc;

// main.c
void check_user_namespace(void);
char *guess_shell(void);

// sandbox.c
int sandbox(void* sandbox_arg);
void start_application(void);

// network_main.c
void net_configure_bridge(Bridge *br, char *dev_name);
void net_configure_sandbox_ip(Bridge *br);
void net_configure_veth_pair(Bridge *br, const char *ifname, pid_t child);
void net_check_cfg(void);
void net_dns_print(pid_t pid);
void network_main(pid_t child);

// network.c
void net_if_up(const char *ifname);
void net_if_down(const char *ifname);
void net_if_ip(const char *ifname, uint32_t ip, uint32_t mask, int mtu);
void net_if_ip6(const char *ifname, const char *addr6);
int net_get_if_addr(const char *bridge, uint32_t *ip, uint32_t *mask, uint8_t mac[6], int *mtu);
int net_add_route(uint32_t dest, uint32_t mask, uint32_t gw);
uint32_t network_get_defaultgw(void);
int net_config_mac(const char *ifname, const unsigned char mac[6]);
int net_get_mac(const char *ifname, unsigned char mac[6]);
void net_config_interface(const char *dev, uint32_t ip, uint32_t mask, int mtu);

// preproc.c
void preproc_build_firejail_dir(void);
void preproc_mount_mnt_dir(void);

// fs.c
// blacklist files or directoies by mounting empty files on top of them
void fs_blacklist(void);
// remount a directory read-only
void fs_rdonly(const char *dir);
// remount a directory noexec, nodev and nosuid
void fs_noexec(const char *dir);
// mount /proc and /sys directories
void fs_proc_sys_dev_boot(void);
// build a basic read-only filesystem
void fs_basic_fs(void);
// mount overlayfs on top of / directory
char *fs_check_overlay_dir(const char *subdirname, int allow_reuse);
void fs_overlayfs(void);
// chroot into an existing directory; mount exiting /dev and update /etc/resolv.conf
void fs_chroot(const char *rootdir);
void fs_check_chroot_dir(const char *rootdir);

// profile.c
// find and read the profile specified by name from dir directory
int profile_find(const char *name, const char *dir);
// read a profile file
void profile_read(const char *fname);
// check profile line; if line == 0, this was generated from a command line option
// return 1 if the command is to be added to the linked list of profile commands
// return 0 if the command was already executed inside the function
int profile_check_line(char *ptr, int lineno, const char *fname);
// add a profile entry in cfg.profile list; use str to populate the list
void profile_add(char *str);

// list.c
void list(void);
void tree(void);
void top(void);
void netstats(void);

// usage.c
void usage(void);

// join.c
void join(pid_t pid, int argc, char **argv, int index);

// shutdown.c
void shut(pid_t pid);

// restricted_shell.c
int restricted_shell(const char *user);

// arp.c
// returns 0 if the address is not in use, -1 otherwise
int arp_check(const char *dev, uint32_t destaddr, uint32_t srcaddr);
// assign an IP address using arp scanning
uint32_t arp_assign(const char *dev, Bridge *br);

// util.c
void drop_privs(int nogroups);
int mkpath_as_root(const char* path);
void extract_command_name(int index, char **argv);
void logsignal(int s);
void logmsg(const char *msg);
void logargs(int argc, char **argv) ;
void logerr(const char *msg);
int copy_file(const char *srcname, const char *destname, uid_t uid, gid_t gid, mode_t mode);
void copy_file_as_user(const char *srcname, const char *destname, uid_t uid, gid_t gid, mode_t mode);
void copy_file_from_user_to_root(const char *srcname, const char *destname, uid_t uid, gid_t gid, mode_t mode);
void touch_file_as_user(const char *fname, uid_t uid, gid_t gid, mode_t mode);
int is_dir(const char *fname);
int is_link(const char *fname);
char *line_remove_spaces(const char *buf);
char *split_comma(char *str);
int not_unsigned(const char *str);
int find_child(pid_t parent, pid_t *child);
void check_private_dir(void);
void update_map(char *mapping, char *map_file);
void wait_for_other(int fd);
void notify_other(int fd);
char *expand_home(const char *path, const char* homedir);
const char *gnu_basename(const char *path);
uid_t pid_get_uid(pid_t pid);
void invalid_filename(const char *fname);
uid_t get_group_id(const char *group);
int remove_directory(const char *path);
void flush_stdin(void);
void create_empty_dir_as_root(const char *dir, mode_t mode);
void create_empty_file_as_root(const char *dir, mode_t mode);
int set_perms(const char *fname, uid_t uid, gid_t gid, mode_t mode);
void mkdir_attr(const char *fname, mode_t mode, uid_t uid, gid_t gid);
char *read_text_file_or_exit(const char *fname);

// fs_var.c
void fs_var_log(void);	// mounting /var/log
void fs_var_lib(void);	// various other fixes for software in /var directory
void fs_var_cache(void); // various other fixes for software in /var/cache directory
void fs_var_run(void);
void fs_var_lock(void);
void fs_var_tmp(void);
void fs_var_utmp(void);
void dbg_test_dir(const char *dir);

// fs_dev.c
void fs_dev_shm(void);
void fs_private_dev(void);
void fs_dev_disable_sound(void);
void fs_dev_disable_3d(void);

// fs_home.c
// private mode (--private)
void fs_private(void);
// private mode (--private=homedir)
void fs_private_homedir(void);
// private template (--private-template=templatedir)
void fs_private_template(void);
// check new private home directory (--private= option) - exit if it fails
void fs_check_private_dir(void);
// check new private template home directory (--private-template= option) exit if it fails
void fs_check_private_template(void);
void fs_private_home_list(void);


// seccomp.c
char *seccomp_check_list(const char *str);
int seccomp_load(const char *fname);
void seccomp_filter_32(void);
void seccomp_filter_64(void);
int seccomp_filter_drop(int enforce_seccomp);
int seccomp_filter_keep(void);
void seccomp_print_filter(pid_t pid);

// caps.c
int caps_default_filter(void);
void caps_print(void);
void caps_drop_all(void);
void caps_set(uint64_t caps);
void caps_check_list(const char *clist, void (*callback)(int));
void caps_drop_list(const char *clist);
void caps_keep_list(const char *clist);
void caps_print_filter(pid_t pid);

// syscall.c
const char *syscall_find_nr(int nr);
// return -1 if error, 0 if no error
int syscall_check_list(const char *slist, void (*callback)(int syscall, int arg), int arg);

// fs_trace.c
void fs_trace_preload(void);
void fs_trace(void);

// fs_hostname.c
void fs_hostname(const char *hostname);
void fs_resolvconf(void);
char *fs_check_hosts_fiile(const char *fname);
void fs_store_hosts_file(void);
void fs_mount_hosts_file(void);

// rlimit.c
void set_rlimits(void);

// cpu.c
void read_cpu_list(const char *str);
void set_cpu_affinity(void);
void load_cpu(const char *fname);
void save_cpu(void);
void cpu_print_filter(pid_t pid);

// cgroup.c
void save_cgroup(void);
void load_cgroup(const char *fname);
void set_cgroup(const char *path);

// output.c
void check_output(int argc, char **argv);

// netfilter.c
void check_netfilter_file(const char *fname);
void netfilter(const char *fname);
void netfilter6(const char *fname);

// netns.c
void check_netns(const char *nsname);
void netns(const char *nsname);
void netns_mounts(const char *nsname);

// bandwidth.c
void bandwidth_del_run_file(pid_t pid);
void bandwidth_pid(pid_t pid, const char *command, const char *dev, int down, int up);
void network_del_run_file(pid_t pid);
void network_set_run_file(pid_t pid);

// fs_etc.c
void fs_machineid(void);
void fs_private_dir_list(const char *private_dir, const char *private_run_dir, const char *private_list);

// no_sandbox.c
int check_namespace_virt(void);
int check_kernel_procs(void);
void run_no_sandbox(int argc, char **argv);

// env.c
typedef enum {
	SETENV = 0,
	RMENV
} ENV_OP;

void env_store(const char *str, ENV_OP op);
void env_apply(void);
void env_defaults(void);
void env_ibus_load(void);

// fs_whitelist.c
void fs_whitelist(void);

// errno.c
int errno_highest_nr(void);
int errno_find_name(const char *name);
char *errno_find_nr(int nr);
void errno_print(void);

// pulseaudio.c
void pulseaudio_init(void);
void pulseaudio_disable(void);

// fs_bin.c
void fs_private_bin_list(void);

// protocol.c
void protocol_filter_save(void);
void protocol_filter_load(const char *fname);
void protocol_print_filter(pid_t pid);

// restrict_users.c
void restrict_users(void);

// fs_logger.c
void fs_logger(const char *msg);
void fs_logger2(const char *msg1, const char *msg2);
void fs_logger2int(const char *msg1, int d);
void fs_logger3(const char *msg1, const char *msg2, const char *msg3);
void fs_logger_print(void);
void fs_logger_change_owner(void);
void fs_logger_print_log(pid_t pid);

// run_symlink.c
void run_symlink(int argc, char **argv);

// paths.c
char **build_paths(void);
unsigned int count_paths(void);
int program_in_path(const char *program);

// fs_mkdir.c
void fs_mkdir(const char *name);
void fs_mkfile(const char *name);

// x11.c
extern int mask_x11_abstract_socket;
void fs_x11(void);
int x11_display(void);
void x11_start(int argc, char **argv);
void x11_start_xpra(int argc, char **argv);
void x11_start_xephyr(int argc, char **argv);
void x11_block(void);

// ls.c
enum {
	SANDBOX_FS_LS = 0,
	SANDBOX_FS_GET,
	SANDBOX_FS_PUT,
	SANDBOX_FS_MAX // this should always be the last entry
};
void sandboxfs(int op, pid_t pid, const char *path1, const char *path2);

// checkcfg.c
enum {
	CFG_FILE_TRANSFER = 0,
	CFG_X11,
	CFG_BIND,
	CFG_USERNS,
	CFG_CHROOT,
	CFG_SECCOMP,
	CFG_NETWORK,
	CFG_RESTRICTED_NETWORK,
	CFG_FORCE_NONEWPRIVS,
	CFG_WHITELIST,
	CFG_XEPHYR_WINDOW_TITLE,
	CFG_REMOUNT_PROC_SYS,
	CFG_OVERLAYFS,
	CFG_CHROOT_DESKTOP,
	CFG_PRIVATE_HOME,
	CFG_PRIVATE_BIN_NO_LOCAL,
	CFG_FIREJAIL_PROMPT,
	CFG_FOLLOW_SYMLINK_AS_USER,
	CFG_MAX // this should always be the last entry
};
extern char *xephyr_screen;
extern char *xephyr_extra_params;
extern char *netfilter_default;
int checkcfg(int val);
void print_compiletime_support(void);
void x11_xorg(void);

// appimage.c
void appimage_set(const char *appimage_path);
void appimage_clear(void);
const char *appimage_getdir(void);

// appimage_size.c
long unsigned int appimage2_size(const char *fname);

// cmdline.c
void build_cmdline(char **command_line, char **window_title, int argc, char **argv, int index);
void build_appimage_cmdline(char **command_line, char **window_title, int argc, char **argv, int index, char *apprun_path);

// sbox.c
// programs
#define PATH_FNET (LIBDIR "/firejail/fnet")
#define PATH_FIREMON (PREFIX "/bin/firemon")
#define PATH_FSECCOMP (LIBDIR "/firejail/fseccomp")
#define PATH_FCOPY (LIBDIR "/firejail/fcopy")
#define SBOX_STDIN_FILE "/run/firejail/mnt/sbox_stdin"

// bitmapped filters for sbox_run
#define SBOX_ROOT (1 << 0)			// run the sandbox as root
#define SBOX_USER (1 << 1)			// run the sandbox as a regular user
#define SBOX_SECCOMP (1 << 2)		// install seccomp 
#define SBOX_CAPS_NONE (1 << 3)		// drop all capabilities
#define SBOX_CAPS_NETWORK (1 << 4)	// caps filter for programs running network programs
#define SBOX_ALLOW_STDIN (1 << 5)		// don't close stdin
#define SBOX_STDIN_FROM_FILE (1 << 6)	// open file and redirect it to stdin

// run sbox
int sbox_run(unsigned filter, int num, ...);


// git.c
void git_install();
void git_uninstall();

#endif

