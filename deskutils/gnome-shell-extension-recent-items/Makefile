# Created by: Gustau Perez i Querol <gustau.perez@gmail.com>
# $FreeBSD$

PORTNAME=	gnome-shell-extension-recent-items
PORTVERSION=	13
CATEGORIES=	deskutils gnome
MASTER_SITES=	http://www.bananenfisch.net/code/
DISTNAME=	RecentItems-${PORTVERSION}
DIST_SUBDIR=	gnome3

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Recent items extensions for the GNOME3 shell

WRKSRC=		${WRKDIR}/RecentItems@bananenfisch.net

USE_GNOME=	glib20
USE_LDCONFIG=	yes

PKGMESSAGE=	../gnome-shell-extra-extensions/pkg-message.slaves

NO_BUILD=	yes

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/RecentItems@bananenfisch.net
	cd ${WRKSRC} && ${COPYTREE_SHARE} . \
		${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/RecentItems@bananenfisch.net
	@chmod +r ${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/RecentItems@bananenfisch.net/metadata.json

.include <bsd.port.mk>
