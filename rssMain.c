#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "rss_utils.h"
#include "rss.h"

int main(int argc, char **argv)
{
  //default: UNL News
  RssService s = unlNews;

  if(argc > 1) {
    int choice = atoi(argv[1]);
    if(choice == 2) {
      s = huskerNews;
    } else if(choice == 3) {
      s = reddit;
    }
  }

  printf("Using RSS Service: %s (%s%s)\n", s.name, s.host, s.resource);

  char *rawXml = getRssXml(s.host, s.resource);

  xmlDocPtr doc = xmlReadMemory(rawXml, strlen(rawXml), "noname.xml", NULL, 0);
    xmlNode *rootElement = xmlDocGetRootElement(doc);

  if(s.type == RSS2) {
    parseRssXml(rootElement);
  } else if(s.type == ATOM1) {
    parseAtomXml(rootElement);
  } else {
    fprintf(stderr, "Undefined Service Type: %d\n", s.type);
  }

  xmlCleanupParser();
}

