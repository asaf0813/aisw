<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

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

<!DOCTYPE html>
<html>
   <head>
      <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
      <title>상세조회화면</title>
   </head>
   <body>
      <h1>게시물 상세보기</h1>   
      <table>
         <tr>
            <th>등록자</th>
            <td><%= vo.getCreater() %></td>
           <th>등록일</th>
           <td><%= vo.getCreateDate() %></td>
           <th>최종 수정자</th>
           <td><%= vo.getUpdater() %></td>
           <th>최종 수정일</th>
           <td><%= vo.getUpdateDate() %></td>
           <th>조회수</th>
           <td><%= vo.getReadCount() %></td>
        </tr>
        <tr> 
           <th>제목</th>
           <td colspan="9"><%= vo.getTitle() %></td>
        </tr>
        <tr> 
           <th>내용</th>
           <td colspan="9"><%= vo.getContents() %></td>
        </tr>
     </table>
     
     <br/><br/>
     
     <button onclick="window.location.href='./list.jsp'">목록</button>
     <button onclick="window.location.href='./update.jsp?boardId=<%= vo.getBoardId() %>'">수정</button>&nbsp;&nbsp;
     <button onclick="goDeleteExcute()">삭제</button>
     
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