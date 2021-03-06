# Created by: KIMURA Yasuhiro <yasu@utahime.org>
# $FreeBSD$

PORTNAME=	with-editor
PORTVERSION=	2.5.9
DISTVERSIONPREFIX=	v
CATEGORIES=	editors elisp
PKGNAMESUFFIX=	-${EMACS_PORT_NAME}

MAINTAINER=	yasu@utahime.org
COMMENT=	Use the Emacsclient as the $EDITOR of child processes

LICENSE=	GPLv3

BUILD_DEPENDS=	dash.el>0:devel/dash.el
RUN_DEPENDS=	dash.el>0:devel/dash.el

USE_GITHUB=	yes
GH_ACCOUNT=	magit

USES=		gmake makeinfo
USE_EMACS=	yes
NO_ARCH=	yes
INFO=		with-editor
PORTDOCS=	README.md

OPTIONS_DEFINE=	DOCS

MAKE_ENV+=	EFLAGS="-L ${PREFIX}/${EMACS_SITE_LISPDIR}"

PLIST_FILES=	${EMACS_VERSION_SITE_LISPDIR}/with-editor.el \
		${EMACS_VERSION_SITE_LISPDIR}/with-editor.elc \
		${EMACS_VERSION_SITE_LISPDIR}/with-editor-autoloads.el

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/${EMACS_VERSION_SITE_LISPDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/*.el ${WRKSRC}/*.elc ${STAGEDIR}${PREFIX}/${EMACS_VERSION_SITE_LISPDIR}
	${INSTALL_MAN} ${WRKSRC}/*.info ${STAGEDIR}${PREFIX}/${INFO_PATH}
	${INSTALL_MAN} ${WRKSRC}/README.md ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
