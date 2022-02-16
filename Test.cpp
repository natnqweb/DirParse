#include "gtest/gtest.h"
#include "dirparser.h"
#define TestFile "./testDirectory/TEXTFILE2LINES.txt"
#define TestDir "./testDirectory"
#define NOT_EXISTING_PATH "DESACX_:/"
#define WRONG_PATH_FORMAT ":c:sa:c_:A//:b"
TEST(PathValidation, EmptyPathAtStart) {
	Dirparser* dirp = new Dirparser;

  EXPECT_EQ(dirp->get_path(), "");
  delete dirp;
  
}

TEST(PathValidation, NonExistingPath) {
	Dirparser* dirp = new Dirparser;

	EXPECT_EQ(dirp->check_if_path_exists(NOT_EXISTING_PATH), false);
	EXPECT_EQ(dirp->get_path(), "");
	delete dirp;


}

TEST(PathSet, NonExistingPath) {
	Dirparser* dirp = new Dirparser;


	EXPECT_EQ(dirp->set_path(NOT_EXISTING_PATH), false);
	delete dirp;


}
TEST(PathSet, WrongPathFormat) {
	Dirparser* dirp = new Dirparser;


	EXPECT_EQ(dirp->set_path(WRONG_PATH_FORMAT), false);
	delete dirp;


}
TEST(GetNumberOfLines, NotExistingDir) {
	Dirparser* dirp = new Dirparser;


	EXPECT_EQ(dirp->get_num_of_lines_in_file(NOT_EXISTING_PATH), 0);
	delete dirp;
}

TEST(GetNumberOfLines, KnownFileTest) {
	Dirparser* dirp = new Dirparser;
	EXPECT_EQ(dirp->get_num_of_lines_in_file(TestFile), 2);

	delete dirp;
}
TEST(GetNumberOfFilesInDir, KnownEmptyFilesTest) {
	Dirparser* dirp = new Dirparser;
	dirp->set_path(TestDir);
	dirp->parse_all_single_dir();
	EXPECT_EQ(dirp->get_num_of_empty_files(), 0);

	delete dirp;
}