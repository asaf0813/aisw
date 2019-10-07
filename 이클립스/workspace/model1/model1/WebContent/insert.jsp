<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>게시물 등록 화면</title>
	</head>
	<body>
	    <!--
            HTTP : Hyper Text Transfer Protocol => 웹 문서를 구성하고 있는 언어인 HTML을 전송하고 전송받기 위한 통신 규칙
               1. HTTP로 정보 전달시 패킷이라는 형태로 데이터가 전송 됨.
               2. 패킷의 구조는 크게 '헤더', '바디'로 구성됨.
               3. URL은 '헤더'쪽에 작성되어 보내짐 
         -->
         
         <!-- form : 폼내에 존재하는 'input type'의 엘리먼트들의 'value'를 'action'의 'url'로 이동할 때, 파라미터로 만들어줌(매핑시켜줌) => 'name':키, 'value':값 -->
         <!-- 
             method: 데이터를 보내는 방식 (GET, POST) 
               ex) title, contents, creater 데이터를 보낼 때
                  GET: localhost:8080?title=제목&contents=내용&creater=생성자
                     => 주소창을 이용해 데이터를 전달
                     => 브라우저의 기준에 따라서 GET방식의 글자수 제한
                     => 데이터가 URL에 작성되어져 있으므로 => HTTP패킷의 '해더'에 포함되여 서버에 요청
                  POST: localhost:8080
                     => GET방식 보다 데이터를 보낼 수 있는 양은 더 큼
                     => 데이터가 URL에 노출되지 않음
                     => 데이터는 HTTP패킷의 '바디'에 포함되어 서버에 요청
         -->	
		<!-- 등록폼 시작 -->
		<form action="/insert_excute.jsp" method="GET">
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
				</tr>
			</table>
		 	<button type="submit">등록</button>
		</form>
		<!-- 등록폼 끝 -->
	</body>
</html>