library(shiny)
library(shinydashboard)
library(shinyjs)
library(flexdashboard)
library(DT)
library(proxy)
library(reshape2)
library(MASS)

####Domitille COQ--ETCHEGARAY####
####Coralie MULLER###
####JUILLET 2019####
####APPLI PARRAINAGE 2019/2020####


######UI###### 
ui2<-(dashboardPage(
  dashboardHeader(title="Parrainage"),
  dashboardSidebar(
    sidebarMenu(id = "tabs",
                menuItem("Questionnaire", tabName = "quest", icon = icon("readme")),
                menuItem("Résultats",tabName = "Ana", icon = icon("poll"))
    )
  ),
  dashboardBody(
    tags$head(
      tags$link(rel="stylesheet",type = "text/css",href = "custom.css")),
    useShinyjs(),
    # Read data
    tabItems(
      tabItem(tabName = "quest",
              div(id="identify",
                  wellPanel(textInput("Name", "Nom et Prénom"),
                            #textInput("FirstName","Prénom"),
                            radioButtons("year", "Year",
                                         c("M1" = "M1",
                                           "M2" = "M2"))),
                  actionButton(inputId = "actBtnVisualisation", label = "Démarrer",icon = icon("play")
                               
                  )),
              div(id="Questions", h3(textOutput(outputId = "ZERO")),
                  actionButton(inputId="UN",label = "TEST1"),
                  actionButton(inputId="DEUX",label = "TEST2"),
                  actionButton(inputId="TROIS",label = "TEST3"),
                  actionButton(inputId="QUATRE",label = "TEST4"),align="center"
              ),
              div(id="Register",h1("END OF QUESTIONS"),tags$img(src="troll.png",width=500),align="center",
                  actionButton(inputId = "buttonsave", label = "Save",icon = icon("play"), align="center"))
            
      ),
              
                 
      
      tabItem(tabName = "Ana",
              uiOutput("page"))
    ))
))

ui1 <-tagList(
  div(id = "login",
      wellPanel(textInput("userName", "Username"),
                passwordInput("passwd", "Password"),
                br(),actionButton("Login", "Log in"))),
  tags$style(type="text/css", "#login {font-size:10px;   text-align: left;position:absolute;top: 40%;left: 50%;margin-top: -100px;margin-left: -150px;}")
)

ui33 <- fluidPage(column(12,
                         tabBox(title="Analyses des résultats",
                                id="TabAnal",height="800px",width="12",
                                tabPanel("Table",
                                         fileInput("dataFileM1",label = NULL,
                                                   buttonLabel = "Browse...",
                                                   placeholder = "M1 FILE"),
                                         fileInput("dataFileM2",label = NULL,
                                                   buttonLabel = "Browse...",
                                                   placeholder = "M2 FILE"),
                                         div(actionButton(inputId = "act", label = "Visualisation",icon = icon("play"))),
                                         dataTableOutput(outputId="tableM1"),
                                         dataTableOutput(outputId="tableM2")),
                                
                                tabPanel("Algo",div(actionButton(inputId = "match", label = "IT'S A MATCH",icon = icon("play"))),dataTableOutput(outputId="final"))
                         )))


######SERVEUR######

server <- shinyServer(function(input,output,session){
  
  ####QUESTIONNAIRE####
  res=1
  df<-reactiveValues(a=0)
  quest<-reactiveValues(r=1)
  dataquestions <- reactiveValues()
  dataresults <- reactiveValues()
  hide(id="Questions")
  hide(id="Register")
  observeEvent(input$actBtnVisualisation, {
    

    
    #### Write CS  FONCTIONNE
    if(input$year=="M1"){
      res=input$Name
      print(res)
    }else{ 
      res=input$Name}

    dataquestions$table = read.csv("test.csv",header=TRUE,sep=",")
    hide(id="identify")
    show(id="Questions")
    output$ZERO <- renderText({paste(dataquestions$table$QUESTIONS[df$a])})
    updateActionButton(session,"UN",label=dataquestions$table$REP1[df$a])
    updateActionButton(session,"DEUX",label=dataquestions$table$REP2[df$a])
    updateActionButton(session,"TROIS",label=dataquestions$table$REP3[df$a])
    updateActionButton(session,"QUATRE",label=dataquestions$table$REP4[df$a])
  })
  observeEvent((input$UN | input$DEUX | input$TROIS | input$QUATRE), 
               { 
                 df$a= df$a  + 1
                 if(df$a!=(length(dataquestions$table$ID))){
                   output$ZERO <- renderText({paste(dataquestions$table$QUESTIONS[df$a])})
                   updateActionButton(session,"UN",label=dataquestions$table$REP1[df$a])
                   updateActionButton(session,"DEUX",label=dataquestions$table$REP2[df$a])
                   updateActionButton(session,"TROIS",label=dataquestions$table$REP3[df$a])
                   updateActionButton(session,"QUATRE",label=dataquestions$table$REP4[df$a])
                 }else{hide(id="Questions")
                   show(id="Register")
                   }
               })
  observeEvent((input$UN ), 
               { 
                 if(input$year=="M1"){
                  res=paste(res,"1", sep=";")
                   print(res)
                 } else{ 
                   res=paste(res,"1", sep=";")
                   print(res)
                   
}
                 
                 
                 df$a= df$a  + 1
                 if(df$a!=(length(dataquestions$table$ID))){
                   output$ZERO <- renderText({paste(dataquestions$table$QUESTIONS[df$a])})
                   updateActionButton(session,"UN",label=dataquestions$table$REP1[df$a])
                   updateActionButton(session,"DEUX",label=dataquestions$table$REP2[df$a])
                   updateActionButton(session,"TROIS",label=dataquestions$table$REP3[df$a])
                   updateActionButton(session,"QUATRE",label=dataquestions$table$REP4[df$a])
                 }else{hide(id="Questions")
                   show(id="Register")
                   show(id="Save")
                   read.csv(".csv")}
               })
  observeEvent((input$DEUX ), 
               { 
                 if(input$year=="M1"){
                   res=paste(res,"2", sep=";")
                   print(res)
                 } else{ 
                   res=paste(res,"2", sep=";")
                   print(res)
                   
                 }
                 
                 
                 df$a= df$a  + 1
                 if(df$a!=(length(dataquestions$table$ID))){
                   output$ZERO <- renderText({paste(dataquestions$table$QUESTIONS[df$a])})
                   updateActionButton(session,"UN",label=dataquestions$table$REP1[df$a])
                   updateActionButton(session,"DEUX",label=dataquestions$table$REP2[df$a])
                   updateActionButton(session,"TROIS",label=dataquestions$table$REP3[df$a])
                   updateActionButton(session,"QUATRE",label=dataquestions$table$REP4[df$a])
                 }else{hide(id="Questions")
                   show(id="Register")
                   show(id="Save")
                   read.csv(".csv")}
               })
  observeEvent((input$TROIS ), 
               { 
                 if(input$year=="M1"){
                   res=paste(res,"3", sep=";")
                   print(res)
                 } else{ 
                   res=paste(res,"3", sep=";")
                   print(res)
                   
                 }
                 
                 
                 df$a= df$a  + 1
                 if(df$a!=(length(dataquestions$table$ID))){
                   output$ZERO <- renderText({paste(dataquestions$table$QUESTIONS[df$a])})
                   updateActionButton(session,"UN",label=dataquestions$table$REP1[df$a])
                   updateActionButton(session,"DEUX",label=dataquestions$table$REP2[df$a])
                   updateActionButton(session,"TROIS",label=dataquestions$table$REP3[df$a])
                   updateActionButton(session,"QUATRE",label=dataquestions$table$REP4[df$a])
                 }else{hide(id="Questions")
                   show(id="Register")
                   show(id="Save")
                   read.csv(".csv")}
               })
  
  observeEvent((input$QUATRE), 
               { 
                 if(input$year=="M1"){
                   res=paste(res,"4", sep=";")
                   print(res)
                 } else{ 
                   res=paste(res,"4", sep=";")
                   print(res)
                   
                 }
                 
                 
                 df$a= df$a  + 1
                 if(df$a!=(length(dataquestions$table$ID))){
                   output$ZERO <- renderText({paste(dataquestions$table$QUESTIONS[df$a])})
                   updateActionButton(session,"UN",label=dataquestions$table$REP1[df$a])
                   updateActionButton(session,"DEUX",label=dataquestions$table$REP2[df$a])
                   updateActionButton(session,"TROIS",label=dataquestions$table$REP3[df$a])
                   updateActionButton(session,"QUATRE",label=dataquestions$table$REP4[df$a])
                 }else{hide(id="Questions")
                   show(id="Register")
                   show(id="Save")
                   read.csv(".csv")}
               })
  
  observeEvent((input$buttonsave),
      if(input$year=="M1"){
      
        write.table(res, file = "M1.csv", row.names= FALSE, col.names = FALSE, append = TRUE )
     }else{ 
      write.table(res , file = "M2.csv",row.names= FALSE, col.names = FALSE, append = TRUE)},
      # hide(id="Register"),
      # hide(id="Save"),
      # show(id="identify")
    
  )
  
  
  ####RESULTATS####
  ####LECTURE DES CSV####
  data<-reactiveValues()
  observeEvent(input$act, {
    if(!is.null(input$dataFileM1$datapath)|!is.null(input$dataFileM2$datapath)){
      # Read input file
      data$M1 = read.csv(file=input$dataFileM1$datapath,
                         header = TRUE,
                         row.names="X")
      data$M2 = read.csv(file=input$dataFileM2$datapath,
                         header = TRUE,
                         row.names = "X")
      
      output$tableM1 <- DT::renderDataTable(data$M1)
      output$tableM2 <- DT::renderDataTable(data$M2)}})
  
  ####ALGO MATCHER####
  observeEvent(input$match, {
    final<-data.frame()
    test<-simil(data$M1,data$M2)
    res<-as.data.frame.matrix(test)
    res<- melt(as.matrix(res),varnames=c("M1","M2"))
    df <- res[order(-res$value),]
    
    
    for(i in 1:9){
      final<-rbind(final,df[1,])
      
      
      df<-subset(df,df$M1!=df$M1[1])
      df<-subset(df,df$M2!=df$M2[1])
    }
    output$final <- DT::renderDataTable(final)
  })
  
  
  ######LOGIN######
  Logged = FALSE;
  my_username <- "Omnia"
  my_password <- "Sakura"
  
  USER <- reactiveValues(Logged=Logged)
  observe({
    if (USER$Logged==FALSE){
      if(!is.null(input$Login)){
        if(input$Login>0){
          Username <- isolate(input$userName)
          Password <- isolate(input$passwd)
          Id.username <- which(my_username == Username)
          Id.password <- which(my_password == Password)
          if (length(Id.username) > 0 & length(Id.password) > 0) {
            if (Id.username == Id.password) {
              USER$Logged <- TRUE
            }
          }
        }
      }
    }
  })
  output$page <- renderUI({
    if(USER$Logged){
      return({  div(class="outer",do.call(bootstrapPage,c("",ui33)))  })
      
    }else{
      return({  div(class="outer",do.call(bootstrapPage,c("",ui1)))    })
      
    }
  })
})

shinyApp(ui=ui2,server=server)

