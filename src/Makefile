# name of the program (Minix service)
PROG=proj 

.PATH: ${.CURDIR}/sprites
.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/devices/graphic
.PATH: ${.CURDIR}/devices/mouse
.PATH: ${.CURDIR}/devices/keyboard
.PATH: ${.CURDIR}/devices/timer
.PATH: ${.CURDIR}/devices/rtc
.PATH: ${.CURDIR}/gamelogic
.PATH: ${.CURDIR}/gamelogic/elements
.PATH: ${.CURDIR}/gamelogic/elements/enemies
.PATH: ${.CURDIR}/gamelogic/elements/towers
.PATH: ${.CURDIR}/gamelogic/menus
.PATH: ${.CURDIR}/gamelogic/states
.PATH: ${.CURDIR}/gamelogic/utils

# source code files to be compiled
SRCS = main.c timer.c mouse.c kbd.c graphics.c rtc.c sprite.c list.c menu.c position.c enemy_constructors.c enemy.c projectile.c tower_constructors.c tower.c game.c leaderboard.c utils.c p_list.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -DPROJ

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
