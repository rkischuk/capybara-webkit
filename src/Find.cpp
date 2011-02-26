#include "Find.h"
#include "Command.h"
#include "WebPage.h"
#include <iostream>

Find::Find(WebPage *page, QObject *parent) : Command(page, parent) {
}

void Find::receivedArgument(const char *xpath) {
  std::cout << "<< Running query: " << xpath << std::endl;
  QString javascript = QString("Capybara.find(\"") + xpath + "\")";

  std::cout << "<< Javascript to execute:" << std::endl;
  std::cout << javascript.toAscii().data() << std::endl;

  QString response;
  QVariant result = page()->mainFrame()->evaluateJavaScript(javascript);

  if (result.isValid()) {
    QVariantList nodes = result.toList();
    bool addComma = false;

    double node;
    for (int i = 0; i < nodes.size(); i++) {
      node = nodes[i].toDouble();
      if (addComma)
        response.append(",");
      response.append(QString::number(node));
      addComma = true;
    }

    std::cout << "<< Got result:" << std::endl;
    std::cout << response.toAscii().data() << std::endl;

    emit finished(true, response);
  } else {
    response = "Invalid XPath expression";
    emit finished(false, response);
  }
}
