#ifndef __SCANTREE_HPP__
#define __SCANTREE_HPP__
/*
scantree.hpp

������������ �������� �������� �, �����������, ������������ ��
������� ���� ������

*/

/* Revision: 1.07 14.06.2003 $ */

/*
Modify:
  14.06.2003 SVS
    ! ��������� ����� ������
    ! ������ SecondPass[] � FindHandle[] ������ ��������� ScanTreeData
    + InsideJunction() - ��� ��������� ������� ������ ��� - "�� � ��������?"
    ! FRS_SCANJUNCTION -> FRS_SCANSYMLINK
  01.06.2003 SVS
    ! ��������� �� BitFlags
  27.12.2002 VVM
    + ����� �������� ScanFlags. ������ �����. ���� ��� ������ ���� SF_FILES_FIRST.
  23.06.2002 SVS
    ! ������� ������� ;-)
  26.03.2002 DJ
    ! GetNextName() ��������� ������ ������ ��� ����� �����
  25.06.2001 IS
    ! ��������� const
  06.05.2001 DJ
    ! �������� #include
  25.06.2000 SVS
    ! ���������� Master Copy
    ! ��������� � �������� ���������������� ������
*/

#include "farconst.hpp"
#include "bitflags.hpp"

enum{
  // ��� ����� ����� ������� ������ (������� 8 ���)
  FSCANTREE_RETUPDIR         = 0x00000001, // = FRS_RETUPDIR
  FSCANTREE_RECUR            = 0x00000002, // = FRS_RECUR
  FSCANTREE_SCANSYMLINK      = 0x00000004, // = FRS_SCANSYMLINK

  // � ������� ����� ������� 8 ���� ���������!
  FSCANTREE_SECONDPASS       = 0x00002000, // ��, ��� ������ ���� ���� SecondPass[]
  FSCANTREE_SECONDDIRNAME    = 0x00004000,
  FSCANTREE_INSIDEJUNCTION   = 0x00008000, // - �� ������ ��������?

  // ����� �� �����, ������� ����� ������������ � 3-� ��������� SetFindPath()
  FSCANTREE_FILESFIRST       = 0x00010000, // ������������ ������� �� ��� �������. ������� �����, ����� ��������
};

struct ScanTreeData{
  BitFlags Flags;
  HANDLE FindHandle;
};

class ScanTree
{
  private:
    BitFlags Flags;
    struct ScanTreeData Data[NM/2];
    int FindHandleCount;
    char FindPath[4*NM];
    char FindMask[NM];

  private:
    void Init();

  public:
    ScanTree(int RetUpDir,int Recurse=1,int ScanJunction=-1);
    ~ScanTree();

  public:
    // 3-� �������� - ����� �� �������� �����
    void SetFindPath(const char *Path,const char *Mask, const DWORD NewScanFlags = FSCANTREE_FILESFIRST);
    int GetNextName(WIN32_FIND_DATA *fdata,char *FullName, size_t BufSize);
    void SkipDir();
    int IsDirSearchDone() {return Flags.Check(FSCANTREE_SECONDDIRNAME);};
    int InsideJunction()   {return Flags.Check(FSCANTREE_INSIDEJUNCTION);};
};

#endif	// __SCANTREE_HPP__
