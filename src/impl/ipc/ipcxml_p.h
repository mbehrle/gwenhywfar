/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Sat Nov 15 2003
    copyright   : (C) 2003 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef GWENHYWFAR_IPCXML_P_H
#define GWENHYWFAR_IPCXML_P_H

#include <gwenhywfar/ipcxml.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/hbcimsg.h>


struct GWEN_IPCXMLREQUEST {
  GWEN_IPCXMLREQUEST *next;
  unsigned int id;
  unsigned int msgLayerId;
  unsigned int dialogId;
  unsigned int messageNumber;
  unsigned int segmentNumber;
  GWEN_DB_NODE *db;
};


struct GWEN_IPCXMLSERVICE {
  GWEN_SERVICELAYER *serviceLayer;
  GWEN_SECCTX_MANAGER *securityManager;
  GWEN_MSGENGINE *msgEngine;

  GWEN_IPCXMLREQUEST *outgoingRequests;
  GWEN_IPCXMLREQUEST *incomingRequests;

};



GWEN_IPCCONNLAYER *GWEN_IPCXMLService_CreateCL(GWEN_IPCXMLSERVICE *xs,
                                               GWEN_IPCXMLSERVICE_TYPE st,
                                               const char *localContext,
                                               unsigned int userMark,
                                               const char *addr,
                                               unsigned int port,
                                               unsigned int flags);

GWEN_ERRORCODE GWEN_IPCXMLService_HandleMsg(GWEN_IPCXMLSERVICE *xs,
                                            GWEN_HBCIMSG *hmsg);

int GWEN_IPCXMLService_AddSecurityGroup(GWEN_HBCIMSG *hmsg,
                                        GWEN_DB_NODE *n);

GWEN_IPCXMLREQUEST *GWEN_IPCXMLService_GetInRequest(GWEN_IPCXMLSERVICE *xs,
                                                    unsigned int id);
GWEN_IPCXMLREQUEST *GWEN_IPCXMLService_GetOutRequest(GWEN_IPCXMLSERVICE *xs,
                                                     unsigned int id);



#endif



