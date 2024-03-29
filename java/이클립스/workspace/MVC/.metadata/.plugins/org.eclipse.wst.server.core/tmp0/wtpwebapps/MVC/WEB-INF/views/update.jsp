<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>


<!DOCTYPE html>
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<title>수정화면</title>
	</head>
	<body>
		<div style="width:1300px; margin:0 auto">
			<h1 style="text-align:center">게시물 수정하기</h1>
			
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
				<form action="/update_excute?" method="get" name="form">
				<!-- boardId 안보이도록 input type="hidden" -->
				<input type="hidden" name="boardId"  value="${vo.boardId}"/>
				
				<!-- 테이블 -->
				<table BORDERCOLOR="#000000" border="1" cellspacing="0" style="width:100%">
					<tr>
						<th width="100" height="30" nowrap >등록자</th>
						<td width="150" align="center">${vo.creater}</td>
						<th width="100" nowrap >등록일</th>
						<td width="150" align="center">${vo.createDate}</td>
						<th width="100" nowrap >조회수</th>
						<td width="150" align="center">${vo.readCount}</td>
					</tr>    
					<tr> 
						<th height="30" nowrap >제목</th>
						<td colspan="5"><input type="text" name="title" style="width:100%" value="${vo.title}"/></td>
					</tr>
					<tr>
						<th height="30" nowrap >수정자</th>
						<td colspan="5"><input type="text" name="updater" style="width:100%" value="${vo.updater}"/></td>
					</tr>
					<tr> 
						<th height="320">내용</th>
						<td colspan="5">
							<textarea name="contents" title="내용" class="textarea" cols="77" rows="20" style="width:100%">${vo.contents}</textarea>
						</td>
					</tr>
					<tr> 
				</table>
				<!-- //테이블 -->
				
				<br/><br/>
				
				<!-- button 그룹 -->
				<div>
					<span style="float:left">
						<button type="button" onclick="window.location.href='/list'">목록</button>
					</span>
					<span style="float:right">
						<!-- <button type="button" onclick="goUpdateExcute()">유효성 검사 후 수정</button>  -->
						<button type="submit">수정</button><!-- 'type'이 submit일 때만 'form'에 있는 'action'속성의 'url'로 페이지 이동을 함 -->&nbsp;&nbsp;
						<button type="button" onclick="window.location.href='/view?boardId=${vo.boardId}'">취소</button>
					</span>
				</div>
				<!-- //button 그룹 -->
			</form>
		</div>
	</body>
	
	<script>
		function validationCheck () {
			var title = document.form.title;
			var contents = document.form.contents;
			var updater = document.form.updater;
			
			if (title.value == "") {
				alert("제목을 입력해주세요.")
				title.focus();
				return false;
			}
			
			if (contents.value == "") {
				alert("내용을 입력해주세요.")
				contents.focus();
				return false;
			}
			
			if (updater.value == "") {
				alert("수정자를 입력해주세요.")
				updater.focus();
				return false;
			}
			
			return true;
		}
	
		function goUpdateExcute() {
			if (validationCheck() == true) {
				document.form.submit();
			}
		}
		
	</script>
</html>