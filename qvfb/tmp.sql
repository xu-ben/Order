BEGIN TRANSACTION;
CREATE TABLE menu(ID Integer primary key, Name varchar(20), Type varchar(20), Imagepath varchar(40), Price real);
INSERT INTO "menu" VALUES(1,'jiucaihezi','stable food','./images/jiucaihezi.png',5.0);
INSERT INTO "menu" VALUES(2,'layouconghuajuan','stable food','./images/layouconghuajuan.png',5.0);
INSERT INTO "menu" VALUES(3,'lvdouzongzi','stable food','./images/lvdouzongzi.png',3.0);
INSERT INTO "menu" VALUES(4,'paiguzongzi','stable food','./images/paiguzongzi.png',6.5);
INSERT INTO "menu" VALUES(5,'tudoujiangbaozi','stable food','./images/tudoujiangbaozi.png',1.5);
INSERT INTO "menu" VALUES(6,'yuxiangrousi','dishes food','./images/yuxiangrousi.png',12.0);
INSERT INTO "menu" VALUES(7,'xianglajinqiandan','dishes food','./images/xianglajinqiandan.png',6.0);
INSERT INTO "menu" VALUES(8,'xiangguchaoyoucai','dishes food','./images/xiangguchaoyoucai.png',5.0);
INSERT INTO "menu" VALUES(9,'tudoushaoe','dishes food','./images/tudoushaoe.png',15.0);
INSERT INTO "menu" VALUES(10,'xiangjiandiaoziyu','dishes food','./images/xiangjiandiaoziyu.png',18.0);
INSERT INTO "menu" VALUES(11,'huadanxiaren','dishes food','./images/huadanxiaren.png',15.0);
INSERT INTO "menu" VALUES(12,'hongjiaochaomaodou','dishes food','./images/hongjiaochaomaodou.png',8.0);
INSERT INTO "menu" VALUES(13,'kuguageliqinghuotang','soup_porridge','./images/kuguageliqinghuotang.png',20.0);
INSERT INTO "menu" VALUES(14,'yinerlianzigeng','soup_porridge','./images/yinerlianzigeng.png',10.0);
INSERT INTO "menu" VALUES(15,'niuroubocaizhou','soup_porridge','./images/niuroubocaizhou.png',12.0);
INSERT INTO "menu" VALUES(16,'wuhuaduntoufu','soup_porridge','./images/wuhuaduntoufu.png',12.0);
COMMIT;
