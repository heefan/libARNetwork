//
//  ViewController.h
//  manager
//
//  Created by Nicolas Payot on 12/11/12.
//  Copyright (c) 2012 Parrot SA. All rights reserved.
//

#import <UIKit/UIKit.h>

#include <libNetwork/manager.h>

#import "TextViewConsole.h"

#import "AppDelegate.h"

@interface ViewController : UIViewController
{

    IBOutlet UITextField* textfieldIP;
    //IBOutlet UITextField* textfieldChar;
    //IBOutlet UITextField* textfieldIntAck;
    IBOutlet UITextField* textfieldType;

    IBOutlet UIButton* buttonCreate;
    IBOutlet UIButton* buttonConnection;
    IBOutlet UIButton* buttonSendChar;
    IBOutlet UIButton* buttonSendIntAck;
    IBOutlet UIButton* buttonSendStrAck;
    IBOutlet UIButton* buttonExit;
    
    IBOutlet TextViewConsole* textViewInfo;
    IBOutlet TextViewConsole* textViewInfoRecv;
    
    //id delegate;
    
    AppDelegate* pAppDelegate;

}

@property (nonatomic, retain) AppDelegate* pAppDelegate;
@property (nonatomic, readonly) IBOutlet TextViewConsole* textViewInfo;
@property (nonatomic, readonly) IBOutlet TextViewConsole* textViewInfoRecv;
//@property(nonatomic,assign)   id  delegate;


- (IBAction)clickCreate;
- (IBAction)clickConnection;

- (IBAction)clcikSendChar;
- (IBAction)clcikSendIntAck;
- (IBAction)clcikSendStrAck;

- (IBAction)clcikExit;


@end