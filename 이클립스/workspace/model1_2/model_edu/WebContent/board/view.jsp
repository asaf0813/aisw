<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8"%>
<%@ page import="model1.vo.Board" %>  
<%@ page import="model1.dao.BoardDAO" %>  
<%
  //현재 페이지로 요청한 boardId
    int boardId = Integer.parseInt(request.getParameter("boardId"));

  //게시판의 DataAccessObject(DAO) 객체 생성
    BoardDAO dao = new BoardDAO();
   //상세페이지로 오면서 조회수 업데이트
    dao.readCountUpdate(boardId);
  //현재 페이지로 요청한 boardId의 게시물 정보 조회
    Board vo = dao.getBoardInfo(boardId);
%>

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

		<div class="divide"></div>

		<div class="body"> 

			<div class="modify_user" >
				<table>
					<tr> 
						<th width="15%" height="23" nowrap>번호</th>
						<td width="15%"><%= vo.getBoardId() %></td>
						<th width="15%" height="23" nowrap >조회수</th>
						<td width="15%"><%= vo.getReadCount() %></td>
					</tr>
					<tr>
						<th width="15%" height="23">등록자</th>
						<td width="15%"><%= vo.getCreater() %></td>
						<th width="15%">등록일</th>
						<td width="15%"><%= vo.getCreateDate() %></td>
					</tr>
					<tr> 
						<th width="15%" height="23" nowrap >제목</th>
						<td width="15%" colspan="3"><%= vo.getTitle() %></td>
					</tr>
					<tr> 
						<th width="15%" height="23">내용</th>
						<td width="15%" colspan="3" height="200"><%= vo.getContents() %></td>
					</tr>
				</table>
			</div>
			<br />
			<div class="buttons">	                      
			     <button onclick="window.location.href='./list.jsp'">목록</button>
			     <button onclick="window.location.href='./update.jsp?boardId=<%= vo.getBoardId() %>'">수정</button>&nbsp;&nbsp;
			     <button onclick="goDeleteExcute()">삭제</button>			
			</div>
		</div>
	</body>
  <script>
  function goDeleteExcute(){
     if(confirm("삭제하시겠습니까?")){
        document.location.href = "./delete_excute.jsp?boardId=<%= vo.getBoardId() %>";
     } else {
        alert("취소되었습니다.");
     }
  }
  </script>
</html>
