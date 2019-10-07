<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    
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
  //삭제하기
  	dao.deleteBoard(boardId);
%>

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<script>
		alert("삭제완료")  // 경고창 뜨고 확인버튼 누르면 페이지이동
		window.location.href = "./list.jsp";
	</script>
</body>
</html>