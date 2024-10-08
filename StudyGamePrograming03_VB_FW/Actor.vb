﻿Imports System.Numerics

Public Class Actor
    Implements IDisposable      '明示的にクラスを開放するために必要

    Public Enum State
        EActive     '稼働中
        EPaused     '休止中
        EDead       '削除対象
    End Enum
    Private mState As State              ' アクターの状態
    Private mPosition As Vector2        '位置
    Private mScale As Single            '拡大率
    Private mRotation As Single         '回転
    Private mRadius As Single           '半径（拡大率は無視）
    Private mComponents As New List(Of Component)   '各コンポーネントのリスト
    Private mGame As Game   'Gameクラスのメンバにアクセスするための変数

    Sub New(ByRef game As Game)
        mState = State.EActive
        mPosition = Vector2.Zero
        mScale = 1.0
        mRotation = 0.0
        mRadius = 0.0
        mGame = game
        mGame.AddActor(Me)
    End Sub
    Protected disposed = False     '開放処理が実施済みかのフラグ
    Public Overloads Sub Dispose() Implements IDisposable.Dispose
        Dispose(True)
    End Sub
    Protected Overridable Overloads Sub Dispose(ByVal disposing As Boolean)
        If Not Me.disposed Then
            If disposing Then
                '*** アンマネージリソースの開放

            End If
            '*** マネージドリソースの開放
            mGame.RemoveActor(Me)
            While mComponents.Count > 0
                mComponents.First.Dispose()
            End While
        End If
        disposed = True
    End Sub
    Protected Overrides Sub Finalize()
        MyBase.Finalize()
        Dispose(False)
    End Sub

    'ゲームから呼び出される更新関数(オーバーライド不可)
    Public Sub Update(ByVal deltaTime As Single)
        If mState = State.EActive Or mState = State.EPaused Then
            For Each comp In mComponents
                comp.Update(deltaTime)
            Next
            UpdateActor(deltaTime)
        End If
    End Sub

    'アクター独自の更新処理(オーバーライド可能)
    Public Overridable Sub UpdateActor(ByVal deltaTime As Single)
    End Sub

    'ゲームから呼び出されるProcess Input(オーバーライド不可)
    Public Sub ProcessInput(ByVal keyState As Boolean())
        If mState = State.EActive Then
            For Each comp In mComponents
                comp.ProcessInput(keyState)
            Next
        End If
        ActorInput(keyState)
    End Sub

    'アクター独自の入力処理(オーバーライド可能)
    Public Overridable Sub ActorInput(ByVal keyState As Boolean())
    End Sub

    'Getters/setters
    Public Function GetPosition() As Vector2
        Return mPosition
    End Function
    Public Sub SetPosition(ByRef pos As Vector2)
        mPosition = pos
    End Sub
    Public Function GetScale() As Single
        Return mScale
    End Function
    Public Sub SetScale(ByRef scale As Single)
        mScale = scale
    End Sub
    Public Function GetRotation() As Single
        Return mRotation
    End Function
    Public Sub SetRotation(ByRef rotation As Single)
        mRotation = rotation
    End Sub
    Public Function GetRadius() As Single
        Return mRadius * mScale
    End Function
    Public Sub SetRadius(ByRef radius As Single)
        mRadius = radius
    End Sub
    Public Function GetForward() As Vector2
        Dim v = New Vector2(Math.Cos(mRotation), -Math.Sin(mRotation))       '向きの単位ベクトル
        Return v
    End Function
    Public Function GetState() As State
        Return mState
    End Function
    Public Sub SetState(ByVal state As State)
        mState = state
    End Sub
    Public Function GetGame() As Game
        Return mGame
    End Function

    ' Add/remove components
    Public Sub AddComponent(ByRef component As Component)
        'ソート済みの配列で挿入点を見つける
        Dim myOrder As Integer = component.GetUpdateOrder()
        Dim cnt As Integer = mComponents.Count     '配列の要素数
        Dim i As Integer = 0
        If cnt > 0 Then
            For i = 0 To mComponents.Count - 1
                If myOrder < mComponents(i).GetUpdateOrder() Then
                    Exit For
                End If
            Next
        End If
        mComponents.Insert(i, component)
    End Sub
    Public Sub RemoveComponent(ByRef component As Component)
        Dim iter As Integer = mComponents.IndexOf(component)
        '見つからなかったら-1が返される。
        If iter >= 0 Then
            mComponents.RemoveAt(iter)
        End If
    End Sub
End Class
