<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8"%>
<!doctype html>
<html lang="en">
	<head>
		<meta charset="UTF-8">
		<meta name="Generator" content="EditPlus®">
		<meta name="Author" content="">
		<meta name="Keywords" content="">
		<meta name="Description" content="">
		<title>insert</title>
		<link href="insert.css" rel="stylesheet" type="text/css" >
		<title>등록 화면</title>
	</head>
	<body>

		<div class="header">
			<a href="../main.jsp">로고</a>
		</div>

		<div class="topnavi_ds">
			<div class="topnavi">  
				<a href="../intro/intro.jsp">회사소개</a> |	
				<a href="../board/list.jsp">게시판</a> | 
				<a href="../member/login.jsp">로그인</a> |
				 <a href="../member/join.jsp">회원가입</a>
			</div>
		</div>

		<div class="divide"></div>

		<div class="body">
			<form action="/board/insert_excute.jsp" method="GET">
				<div class="modify_user">
						<table>
							<tr>
								<td>제목</td>
								<td><input type="text" name="title"></td>
							</tr>
							<tr>
								<td>작성자</td>
								<td><input type="text" name="creater"></td>
							</tr>
							<tr>
								<td>내용</td>
								<td><textarea name="contents"></textarea></td>
						</table>
					<button type="submit">등록</button>		
				</div>			
			</form>
		</div>
	</body>
</html>
