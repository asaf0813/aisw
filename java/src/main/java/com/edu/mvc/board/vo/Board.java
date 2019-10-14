package com.edu.mvc.board.vo;

public class Board {
		//게시판 번호
	   private int boardId;
	   
	   //게시판 제목
	   private String title;
	   
	   //게시판 내용
	   private String contents;
	   
	   //등록자
	   private String creater;
	   
	   //등록일
	   private String createDate;
	   
	   //수정자
	   private String updater;
	   
	   //수정일
	   private String updateDate;
	   
	   //조회수
	   private int readCount;

	   public int getBoardId() {
	      return boardId;
	   }

	   public void setBoardId(int boardId) {
	      this.boardId = boardId;
	   }

	   public String getTitle() {
	      return title;
	   }

	   public void setTitle(String title) {
	      this.title = title;
	   }

	   public String getContents() {
	      return contents;
	   }

	   public void setContents(String contents) {
	      this.contents = contents;
	   }

	   public String getCreater() {
	      return creater;
	   }

	   public void setCreater(String creater) {
	      this.creater = creater;
	   }

	   public String getCreateDate() {
	      return createDate;
	   }

	   public void setCreateDate(String createDate) {
	      this.createDate = createDate;
	   }

	   public String getUpdater() {
	      return updater;
	   }

	   public void setUpdater(String updater) {
	      this.updater = updater;
	   }

	   public String getUpdateDate() {
	      return updateDate;
	   }

	   public void setUpdateDate(String updateDate) {
	      this.updateDate = updateDate;
	   }

	   public int getReadCount() {
	      return readCount;
	   }

	   public void setReadCount(int readCount) {
	      this.readCount = readCount;
	   }
}
