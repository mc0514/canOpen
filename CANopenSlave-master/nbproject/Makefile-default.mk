#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Slave.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Slave.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/CO_CANDRV.o ${OBJECTDIR}/CO_COMM.o ${OBJECTDIR}/CO_DEV.o ${OBJECTDIR}/CO_dict.o ${OBJECTDIR}/CO_MAIN.o ${OBJECTDIR}/CO_MEMIO.o ${OBJECTDIR}/CO_NMT.o ${OBJECTDIR}/CO_NMTE.o ${OBJECTDIR}/CO_PDO.o ${OBJECTDIR}/CO_PDO1.o ${OBJECTDIR}/CO_PDO2.o ${OBJECTDIR}/CO_PDO3.o ${OBJECTDIR}/CO_PDO4.o ${OBJECTDIR}/CO_SDO1.o ${OBJECTDIR}/CO_SYNC.o ${OBJECTDIR}/CO_TOOLS.o ${OBJECTDIR}/IOutils.o ${OBJECTDIR}/main.o ${OBJECTDIR}/NMTextension.o ${OBJECTDIR}/Slave.o ${OBJECTDIR}/Timer.o
POSSIBLE_DEPFILES=${OBJECTDIR}/CO_CANDRV.o.d ${OBJECTDIR}/CO_COMM.o.d ${OBJECTDIR}/CO_DEV.o.d ${OBJECTDIR}/CO_dict.o.d ${OBJECTDIR}/CO_MAIN.o.d ${OBJECTDIR}/CO_MEMIO.o.d ${OBJECTDIR}/CO_NMT.o.d ${OBJECTDIR}/CO_NMTE.o.d ${OBJECTDIR}/CO_PDO.o.d ${OBJECTDIR}/CO_PDO1.o.d ${OBJECTDIR}/CO_PDO2.o.d ${OBJECTDIR}/CO_PDO3.o.d ${OBJECTDIR}/CO_PDO4.o.d ${OBJECTDIR}/CO_SDO1.o.d ${OBJECTDIR}/CO_SYNC.o.d ${OBJECTDIR}/CO_TOOLS.o.d ${OBJECTDIR}/IOutils.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/NMTextension.o.d ${OBJECTDIR}/Slave.o.d ${OBJECTDIR}/Timer.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/CO_CANDRV.o ${OBJECTDIR}/CO_COMM.o ${OBJECTDIR}/CO_DEV.o ${OBJECTDIR}/CO_dict.o ${OBJECTDIR}/CO_MAIN.o ${OBJECTDIR}/CO_MEMIO.o ${OBJECTDIR}/CO_NMT.o ${OBJECTDIR}/CO_NMTE.o ${OBJECTDIR}/CO_PDO.o ${OBJECTDIR}/CO_PDO1.o ${OBJECTDIR}/CO_PDO2.o ${OBJECTDIR}/CO_PDO3.o ${OBJECTDIR}/CO_PDO4.o ${OBJECTDIR}/CO_SDO1.o ${OBJECTDIR}/CO_SYNC.o ${OBJECTDIR}/CO_TOOLS.o ${OBJECTDIR}/IOutils.o ${OBJECTDIR}/main.o ${OBJECTDIR}/NMTextension.o ${OBJECTDIR}/Slave.o ${OBJECTDIR}/Timer.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Slave.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4680
MP_PROCESSOR_OPTION_LD=18f4680
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0xfd30 -u_DEBUGCODELEN=0x2d0 -u_DEBUGDATASTART=0xcf4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/CO_CANDRV.o: CO_CANDRV.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_CANDRV.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_CANDRV.o   CO_CANDRV.C 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_CANDRV.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_CANDRV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_COMM.o: CO_COMM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_COMM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_COMM.o   CO_COMM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_COMM.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_COMM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_DEV.o: CO_DEV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_DEV.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_DEV.o   CO_DEV.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_DEV.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_DEV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_dict.o: CO_dict.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_dict.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_dict.o   CO_dict.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_dict.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_dict.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_MAIN.o: CO_MAIN.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_MAIN.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_MAIN.o   CO_MAIN.C 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_MAIN.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_MAIN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_MEMIO.o: CO_MEMIO.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_MEMIO.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_MEMIO.o   CO_MEMIO.C 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_MEMIO.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_MEMIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_NMT.o: CO_NMT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_NMT.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_NMT.o   CO_NMT.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_NMT.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_NMT.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_NMTE.o: CO_NMTE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_NMTE.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_NMTE.o   CO_NMTE.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_NMTE.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_NMTE.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO.o: CO_PDO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO.o   CO_PDO.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO1.o: CO_PDO1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO1.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO1.o   CO_PDO1.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO1.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO2.o: CO_PDO2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO2.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO2.o   CO_PDO2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO2.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO3.o: CO_PDO3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO3.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO3.o   CO_PDO3.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO3.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO4.o: CO_PDO4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO4.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO4.o   CO_PDO4.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO4.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_SDO1.o: CO_SDO1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_SDO1.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_SDO1.o   CO_SDO1.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_SDO1.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_SDO1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_SYNC.o: CO_SYNC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_SYNC.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_SYNC.o   CO_SYNC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_SYNC.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_SYNC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_TOOLS.o: CO_TOOLS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_TOOLS.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_TOOLS.o   CO_TOOLS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_TOOLS.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_TOOLS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/IOutils.o: IOutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/IOutils.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/IOutils.o   IOutils.c 
	@${DEP_GEN} -d ${OBJECTDIR}/IOutils.o 
	@${FIXDEPS} "${OBJECTDIR}/IOutils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/NMTextension.o: NMTextension.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NMTextension.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NMTextension.o   NMTextension.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NMTextension.o 
	@${FIXDEPS} "${OBJECTDIR}/NMTextension.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Slave.o: Slave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Slave.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Slave.o   Slave.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Slave.o 
	@${FIXDEPS} "${OBJECTDIR}/Slave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Timer.o: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Timer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Timer.o   Timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Timer.o 
	@${FIXDEPS} "${OBJECTDIR}/Timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/CO_CANDRV.o: CO_CANDRV.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_CANDRV.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_CANDRV.o   CO_CANDRV.C 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_CANDRV.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_CANDRV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_COMM.o: CO_COMM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_COMM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_COMM.o   CO_COMM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_COMM.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_COMM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_DEV.o: CO_DEV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_DEV.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_DEV.o   CO_DEV.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_DEV.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_DEV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_dict.o: CO_dict.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_dict.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_dict.o   CO_dict.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_dict.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_dict.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_MAIN.o: CO_MAIN.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_MAIN.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_MAIN.o   CO_MAIN.C 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_MAIN.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_MAIN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_MEMIO.o: CO_MEMIO.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_MEMIO.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_MEMIO.o   CO_MEMIO.C 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_MEMIO.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_MEMIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_NMT.o: CO_NMT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_NMT.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_NMT.o   CO_NMT.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_NMT.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_NMT.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_NMTE.o: CO_NMTE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_NMTE.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_NMTE.o   CO_NMTE.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_NMTE.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_NMTE.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO.o: CO_PDO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO.o   CO_PDO.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO1.o: CO_PDO1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO1.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO1.o   CO_PDO1.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO1.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO2.o: CO_PDO2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO2.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO2.o   CO_PDO2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO2.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO3.o: CO_PDO3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO3.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO3.o   CO_PDO3.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO3.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_PDO4.o: CO_PDO4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_PDO4.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_PDO4.o   CO_PDO4.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_PDO4.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_PDO4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_SDO1.o: CO_SDO1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_SDO1.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_SDO1.o   CO_SDO1.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_SDO1.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_SDO1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_SYNC.o: CO_SYNC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_SYNC.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_SYNC.o   CO_SYNC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_SYNC.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_SYNC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/CO_TOOLS.o: CO_TOOLS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CO_TOOLS.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CO_TOOLS.o   CO_TOOLS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CO_TOOLS.o 
	@${FIXDEPS} "${OBJECTDIR}/CO_TOOLS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/IOutils.o: IOutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/IOutils.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/IOutils.o   IOutils.c 
	@${DEP_GEN} -d ${OBJECTDIR}/IOutils.o 
	@${FIXDEPS} "${OBJECTDIR}/IOutils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/NMTextension.o: NMTextension.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/NMTextension.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/NMTextension.o   NMTextension.c 
	@${DEP_GEN} -d ${OBJECTDIR}/NMTextension.o 
	@${FIXDEPS} "${OBJECTDIR}/NMTextension.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Slave.o: Slave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Slave.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Slave.o   Slave.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Slave.o 
	@${FIXDEPS} "${OBJECTDIR}/Slave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Timer.o: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Timer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Timer.o   Timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Timer.o 
	@${FIXDEPS} "${OBJECTDIR}/Timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Slave.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG   -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Slave.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/Slave.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w    -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Slave.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
