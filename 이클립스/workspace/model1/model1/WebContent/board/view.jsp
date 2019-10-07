<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8"%>
<!doctype html>
<html lang="en">
	<head>
		<meta charset="UTF-8">
		<meta name="Generator" content="EditPlus®">
		<meta name="Author" content="">
		<meta name="Keywords" content="">
		<meta name="Description" content="">
		<title>view</title>
		<link href="./view.css" rel="stylesheet" type="text/css" >
	</head>
	<body>

		<div class="header">
			<a href="../main.jsp">로고</a>
		</div>

		<div class="topnavi_ds">
			<div class="topnavi">  
				<a href="../intro/intro.jsp">회사소개</a> |	
				<a href="./list.jsp">게시판</a> | 
				<a href="../member/login.jsp">로그인</a> |
				 <a href="../member/join.jsp">회원가입</a>
			</div>
		</div>

		<div class="divide"/>

		<div class="body"> 

			<div class="modify_user" >
				<table>
					<tr> 
						<th width="15%" height="23" nowrap>번호</th>
						<td width="15%">1</td>
						<th width="15%" height="23" nowrap >조회수</th>
						<td width="15%">10</td>
					</tr>
					<tr>
						<th width="15%" height="23">등록자</th>
						<td width="15%">관리자</td>
						<th width="15%">등록일</th>
						<td width="15%">2014-09-20</td>
					</tr>
					<tr> 
						<th width="15%" height="23" nowrap >제목</th>
						<td width="15%" colspan="3">반갑습니다.</td>
					</tr>
					<tr> 
						<th width="15%" height="23">내용</th>
						<td width="15%" colspan="3" height="200">글내용</td>
					</tr>
				</table>
			</div>
			<br />
			<div class="buttons">	                      
				<a href="./list.jsp">목록</a>
			</div>

		</div>

	</body>
</html>
