/*
SQLITE Generation script


*/

/*Lookup tables for faculties and Academics*/

CREATE TABLE Faculty(name VARCHAR(30) NOT NULL);

CREATE TABLE Academic(name VARCHAR(30) NOT NULL);

/*REAL STUFF*/



CREATE TABLE Degree(
		dcode NUMBER(3) NOT NULL,
		dname VARCHAR(30) NOT NULL,
		faculty VARCHAR(30) NOT NULL,
		CONSTRAINT DEG_PK PRIMARY KEY(dcode) );
		
CREATE TABLE Subject(
		scode VARCHAR(8) NOT NULL,
		subreq VARCHAR(8),
		dcode NUMBER(3) NOT NULL,
		academic VARCHAR(30) NOT NULL,
		CONSTRAINT SUBJECT_PK PRIMARY KEY(scode),
		CONSTRAINT SUBJECT_ACADEMIC_FK FOREIGN KEY(academic) REFERENCES Academic(name)
		CONSTRAINT CORE_DCODE_FK FOREIGN KEY(dcode) REFERENCES Degree(dcode) );				
		

CREATE TABLE Classblock(
		subcode VARCHAR(8) NOT NULL,
		cname CHAR(1) NOT NULL,
		length NUMBER(1),
		time NUMBER(2),
		date NUMBER(1),
		CONSTRAINT CLASSBLOCK_FK FOREIGN KEY(subcode) REFERENCES Subject(scode) );
		
CREATE TABLE Assessment(
		scode VARCHAR(8) NOT NULL,
		anum NUMBER(1) NOT NULL,
		percentage NUMBER(2) NOT NULL,
		CONSTRAINT ASSESSMENT_FK FOREIGN KEY(scode) REFERENCES Subject(scode),
		CONSTRAINT ASSESSMENT_PK PRIMARY KEY(scode, anum) );	
		
		