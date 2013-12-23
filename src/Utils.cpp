#include <QTemporaryFile>
#include <fstream>
#include <string>

#include "Utils.hpp"

// very hacky, very simple, very fragile
QList<QString> readProcessLines(QString command)
{
  QTemporaryFile tmpFileIn;
  tmpFileIn.setAutoRemove(true);
  tmpFileIn.open();

  QList<QString> result;

  system((command+ " >" + tmpFileIn.fileName()).toStdString().c_str());
  std::ifstream inputFile(tmpFileIn.fileName().toStdString().c_str());
  while (inputFile) {
    std::string str;
    if (std::getline(inputFile, str)) {
      result.push_back(QString::fromStdString(str));
    }
  }
  return result;
}
