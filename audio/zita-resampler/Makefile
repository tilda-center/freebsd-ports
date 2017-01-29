# Created by: Goran Mekić <meka@tilda.center>
# $FreeBSD$

PORTNAME=	zita-resampler
PORTVERSION=	1.6.0
CATEGORIES=	audio
MASTER_SITES=	http://kokkinizita.linuxaudio.org/linuxaudio/downloads/

MAINTAINER=	meka@tilda.center
COMMENT=	C++ library for resampling audio signals

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		tar:bzip2 gmake
WRKSRC_SUBDIR=	libs

MY_WORKDIR=	${WRKDIR}/${PORTNAME}-${PORTVERSION}
MY_LIB=	${STAGEDIR}${PREFIX}/lib/lib${PORTNAME}.so

post-extract:
	${LN} -s ${MY_WORKDIR}/COPYING ${MY_WORKDIR}/${WRKSRC_SUBDIR}/COPYING

post-install:
	${LN} -s lib${PORTNAME}.so ${MY_LIB}.1

.include <bsd.port.mk>
