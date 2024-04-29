{\rtf1\ansi\ansicpg1252\cocoartf2761
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 WITH TEMP AS\
(SELECT USER_ID\
FROM USER_INFO\
WHERE SUBSTRING(JOINED,1,4) = '2021')\
\
SELECT YEAR(SALES_DATE) AS YEAR, MONTH(SALES_DATE) AS MONTH, COUNT(DISTINCT T1.USER_ID) AS PUCHASED_USERS, ROUND(COUNT(DISTINCT T1.USER_ID) / (SELECT COUNT(USER_ID) FROM TEMP), 1) AS PUCHASED_RATIO\
FROM ONLINE_SALE AS T1\
INNER JOIN TEMP AS T2\
ON T1.USER_ID = T2.USER_ID\
GROUP BY 1,2\
ORDER BY 1, 2\
;}