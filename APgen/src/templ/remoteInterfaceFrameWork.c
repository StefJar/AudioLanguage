// ==================================
// names of the global variables
// ==================================

// a global variable
typedef struct SGlobalVariable {
	int32_t		varID;
	char *		szName;
	void *		pAPVar;
} TGlobalVariable;

// a vector of global variables
typedef struct SGlobalVariableVector {
	TGlobalVariable * 	pFE;
	int					num;
} TGlobalVariableVector;


// global variable holding the vector with the global variables
TGlobalVariableVector gGVV = {NULL, 0};

const char const * gcFileID="EACI01";


int loadGlobalVariablesFromFile (const char * szFileName) {
	FILE * f;
	int i;
	int idL = strlen(gcFileID);
	char idBuffer[idL];
	int32_t intDummy;
	char	charDummy;
	int	endianness;
	TGlobalVariable * pV;


	f = fopen(szFileName,"rb");
	// check id
	idBuffer[idL] = 0;
	if (idL != fread(idBuffer,sizeof(char),idL,f)) {
		fprintf(stderr,"could not read id string");
		fclose(f);
		return -1;
	}
	if (strcmp(idBuffer,gcFileID)) {
		fprintf(stderr,"id string does not match (%s vs %s)",gcFileID,idBuffer);
		fclose(f);
		return -2;
	}
	// read endianness
	if (1 != fread(&charDummy,sizeof(char),1,f)) {
		fprintf(stderr,"could not read the endianness flag");
		fclose(f);
		return -3;
	}
	endianness = (int) charDummy;
	// read element amount
	if (1 != fread(&intDummy,sizeof(int32_t),1,f)) {
		fprintf(stderr,"could not read the endianness flag");
		fclose(f);
		return -4;
	}
	APendianConversation32Bit((uint32_t *)&intDummy,endianness);

	// allocate buffer
	gGVV.pFE = malloc(sizeof(TGlobalVariable) * intDummy);
	if (!gGVV.pFE) {
		fprintf(stderr,"could not allocate memory for the global var vector");
		fclose(f);
		return -5;
	}
	gGVV.num = (int) intDummy;
	memset(gGVV.pFE,(int) NULL, sizeof(TGlobalVariable) * gGVV.num);
	// fill it
	pV = gGVV.pFE;
	for (i = 0; i < gGVV.num; i++) {
		// read var id
		if (1 != fread(&intDummy,sizeof(int32_t),1,f)) {
			fprintf(stderr,"could not read the varID");
			fclose(f);
			return -6;
		}
		APendianConversation32Bit((uint32_t *)&intDummy,endianness);
		pV->varID = intDummy;
		// read length of the name
		if (1 != fread(&intDummy,sizeof(int32_t),1,f)) {
			fprintf(stderr,"could not read the length of the name");
			fclose(f);
			return -7;
		}
		APendianConversation32Bit((uint32_t *)&intDummy,endianness);
		pV->szName = malloc(sizeof(char)*intDummy+1);
		pV->szName[intDummy] = 0;

		if (intDummy != fread(pV->szName,sizeof(char),intDummy,f)) {
			fprintf(stderr,"could not read the variable name");
			fclose(f);
			return -8;
		}
		pV++;
	}
	fclose(f);
	return 0;
}

void printGlobalVariable(FILE * dev, int indx) {
	TGlobalVariable * pV = gGVV.pFE + indx;
	fprintf(dev,"%s (varID=%i)",pV->szName,pV->varID);
}

void freeGlobalVariables () {
	int i;
	TGlobalVariable * pV = gGVV.pFE;

	for (i = 0; i < gGVV.num; i++) {
		if (pV->szName) {
			free(pV->szName);
		}
		pV++;
	}
	free(gGVV.pFE);

	gGVV.pFE = NULL;
	gGVV.num = 0;
}

// ==================================
// main
// ==================================

