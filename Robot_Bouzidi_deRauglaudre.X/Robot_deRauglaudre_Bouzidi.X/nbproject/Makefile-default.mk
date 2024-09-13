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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Robot_deRauglaudre_Bouzidi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Robot_deRauglaudre_Bouzidi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c sources/PWM.c sources/IO.c sources/Robot.c sources/timer.c sources/ToulBox.c sources/ChipConfig.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/sources/PWM.o ${OBJECTDIR}/sources/IO.o ${OBJECTDIR}/sources/Robot.o ${OBJECTDIR}/sources/timer.o ${OBJECTDIR}/sources/ToulBox.o ${OBJECTDIR}/sources/ChipConfig.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/sources/PWM.o.d ${OBJECTDIR}/sources/IO.o.d ${OBJECTDIR}/sources/Robot.o.d ${OBJECTDIR}/sources/timer.o.d ${OBJECTDIR}/sources/ToulBox.o.d ${OBJECTDIR}/sources/ChipConfig.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/sources/PWM.o ${OBJECTDIR}/sources/IO.o ${OBJECTDIR}/sources/Robot.o ${OBJECTDIR}/sources/timer.o ${OBJECTDIR}/sources/ToulBox.o ${OBJECTDIR}/sources/ChipConfig.o

# Source Files
SOURCEFILES=main.c sources/PWM.c sources/IO.c sources/Robot.c sources/timer.c sources/ToulBox.c sources/ChipConfig.c



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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Robot_deRauglaudre_Bouzidi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512MU814
MP_LINKER_FILE_OPTION=,--script="headers/ChipConfig.h"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/46621ee4fb4adb8ec07c48e9efbf5a2e893aa4e9 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/PWM.o: sources/PWM.c  .generated_files/flags/default/bbeb392679fd4ea551fdd7bd735dd6e676c4529 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/PWM.o.d 
	@${RM} ${OBJECTDIR}/sources/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/PWM.c  -o ${OBJECTDIR}/sources/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/PWM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/IO.o: sources/IO.c  .generated_files/flags/default/6bda362338367c9eeb91d7651218c60df2eb1fd6 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/IO.o.d 
	@${RM} ${OBJECTDIR}/sources/IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/IO.c  -o ${OBJECTDIR}/sources/IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/IO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/Robot.o: sources/Robot.c  .generated_files/flags/default/126a056e8692f1e69415254cffe870c58c658f83 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/Robot.o.d 
	@${RM} ${OBJECTDIR}/sources/Robot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/Robot.c  -o ${OBJECTDIR}/sources/Robot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/Robot.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/timer.o: sources/timer.c  .generated_files/flags/default/2af7e3e283051629e999cbd499807010b8acc326 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/timer.o.d 
	@${RM} ${OBJECTDIR}/sources/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/timer.c  -o ${OBJECTDIR}/sources/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/ToulBox.o: sources/ToulBox.c  .generated_files/flags/default/dc13ed8ee89ee9b696e124a81df6b07140952a59 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ToulBox.o.d 
	@${RM} ${OBJECTDIR}/sources/ToulBox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/ToulBox.c  -o ${OBJECTDIR}/sources/ToulBox.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/ToulBox.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/ChipConfig.o: sources/ChipConfig.c  .generated_files/flags/default/79a18d64de970b4c75aaf942661846e563ce68ef .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ChipConfig.o.d 
	@${RM} ${OBJECTDIR}/sources/ChipConfig.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/ChipConfig.c  -o ${OBJECTDIR}/sources/ChipConfig.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/ChipConfig.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/ca1bed4149ef49d7a7c3f1faf7f784ff9931d6f1 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/PWM.o: sources/PWM.c  .generated_files/flags/default/58c009ddb0064468c68c9ffe608221500a6efdae .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/PWM.o.d 
	@${RM} ${OBJECTDIR}/sources/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/PWM.c  -o ${OBJECTDIR}/sources/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/PWM.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/IO.o: sources/IO.c  .generated_files/flags/default/9e7c06f6f9e96e0670658f2b583f5bd9fad87245 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/IO.o.d 
	@${RM} ${OBJECTDIR}/sources/IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/IO.c  -o ${OBJECTDIR}/sources/IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/IO.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/Robot.o: sources/Robot.c  .generated_files/flags/default/42a95fa70f91eabd1fc5da3894ebe6d2afb60ba6 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/Robot.o.d 
	@${RM} ${OBJECTDIR}/sources/Robot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/Robot.c  -o ${OBJECTDIR}/sources/Robot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/Robot.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/timer.o: sources/timer.c  .generated_files/flags/default/79432c49564d21c0994981b897c64252c1df5082 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/timer.o.d 
	@${RM} ${OBJECTDIR}/sources/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/timer.c  -o ${OBJECTDIR}/sources/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/timer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/ToulBox.o: sources/ToulBox.c  .generated_files/flags/default/335dc40238b15a4764311345071db040027a4fef .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ToulBox.o.d 
	@${RM} ${OBJECTDIR}/sources/ToulBox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/ToulBox.c  -o ${OBJECTDIR}/sources/ToulBox.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/ToulBox.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/sources/ChipConfig.o: sources/ChipConfig.c  .generated_files/flags/default/f1a50b9ff175adcd842b76dd300a2935e51feb3 .generated_files/flags/default/e77312e3219c4c8980e2cdd89c84e21dcc112ecd
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ChipConfig.o.d 
	@${RM} ${OBJECTDIR}/sources/ChipConfig.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/ChipConfig.c  -o ${OBJECTDIR}/sources/ChipConfig.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/sources/ChipConfig.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Robot_deRauglaudre_Bouzidi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    headers/ChipConfig.h
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Robot_deRauglaudre_Bouzidi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Robot_deRauglaudre_Bouzidi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   headers/ChipConfig.h
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Robot_deRauglaudre_Bouzidi.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}/xc16-bin2hex ${DISTDIR}/Robot_deRauglaudre_Bouzidi.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
