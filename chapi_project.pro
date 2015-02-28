TEMPLATE = subdirs
SUBDIRS = common chapi blink
chapi.depends = common
blink.depends = common
