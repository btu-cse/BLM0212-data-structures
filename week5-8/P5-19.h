/*	==================== buildList ====================	Reads a text data file and loads the linked list	Pre    file exists in format: yy \t 'pic' \t 'dir'	Post   list contains data	       -or- program aborted if problems*/LIST* buildList (void){//	Local Definitions	FILE* fpData;	LIST* list;	int  idIn;
	char    adIn [STR_MAX];	char    soyadIn[STR_MAX];
	char    bolumIn[STR_MAX];
    int     sinifIn;
	int    addResult;	STUDENT* pStu;//	Statements	list   = createList (cmpIdNum);	if (!list)	    printf("\aCannot create list\n"),	           exit (100);	fpData = fopen("students.dat", "r");	if (!fpData)	    printf("\aError opening input file\n"),	           exit (110);	while (fscanf(fpData, "%d", &idIn) == 1)	   {	    pStu = (STUDENT*) malloc(sizeof(STUDENT));	    if (!(pStu))	        printf("\aOut of Memory in build list\n"),	               exit (100);	    pStu->id = idIn;

	    fscanf(fpData, "\t%s\t%s\t%s\t%d\r",pStu->ad,pStu->soyad,pStu->bolum,&pStu->sinif );

	    // Insert into list	    addResult = addNode (list, pStu);	    if (addResult != 0)	        if (addResult == -1)	            printf("Memory overflow adding movie\a\n"),	                    exit (120);	        else	            printf("Duplicate id %d not added\n\a",	                    pStu->id);
	   } // while	return list;}	// buildList